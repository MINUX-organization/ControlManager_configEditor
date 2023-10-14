#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "configitemmodel.h"

#include "configsLib/configfile.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupModel();
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

