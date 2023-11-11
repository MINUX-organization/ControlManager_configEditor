#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "configitemmodel.h"

#include "configsLib/configfile.h"

#include <QDebug>

#include <msgpack.hpp>

struct testStruct
{
    std::string abobaData {"TEST DATA IS DATA"};
    int intData {1};
    MSGPACK_DEFINE(abobaData, intData)
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupModel();

    try
    {
        testStruct ts;
        ConfigsLib::ConfigFile cf(false);
        std::string buffer;

        if (!cf.setFile("testFile.txt"))
        {
            if (!cf.createFile("testFile.txt"))
            {
                qDebug() << "Error creating file:" << cf.errorText();
            }
        }
        cf.clearBuffer();

        for (int i = 0; i < 10; i++)
        {
            ts.abobaData = std::string("Its class ") + std::to_string(i);
            ts.intData = i;
            buffer = cf.compressClass(ts);
            cf.addClass(buffer);
        }
        if (!cf.save())
        {
            qDebug() << "Shit:" << cf.errorText();
            throw "aboba";
        }


        cf.clearBuffer();
        cf.load();
        ts.intData = 0;
        ts.abobaData = "";
        for (int i = 0; i < cf.classesCount(); i++)
        {
            buffer = cf.getClass(i);
            ts = cf.decompressClass<testStruct>(buffer);
            qDebug() << ts.abobaData.c_str() << ts.intData;
        }
    }
    catch (std::exception & ex)
    {
        qDebug() << ex.what();
    }
    catch (...)
    {
        qDebug() << "Catched exception";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    m_pConfigModel = new ConfigItemModel::ConfigItemTreeModel(this);

    m_pConfigModel->update();

    ui->configFile_treeView->setModel(m_pConfigModel);
}

