/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLineEdit *filePath_lineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *save_pushButton;
    QPushButton *load_pushButton;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *jsonOutput_radioButton;
    QRadioButton *configOutput_radioButton;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *addOption_pushButton;
    QPushButton *editOption_pushButton;
    QPushButton *removeOption_pushButton;
    QProgressBar *progressBar;
    QTreeView *configFile_treeView;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(803, 639);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer, 2, 2, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        filePath_lineEdit = new QLineEdit(widget);
        filePath_lineEdit->setObjectName(QString::fromUtf8("filePath_lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(filePath_lineEdit->sizePolicy().hasHeightForWidth());
        filePath_lineEdit->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(filePath_lineEdit, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        save_pushButton = new QPushButton(widget);
        save_pushButton->setObjectName(QString::fromUtf8("save_pushButton"));

        horizontalLayout->addWidget(save_pushButton);

        load_pushButton = new QPushButton(widget);
        load_pushButton->setObjectName(QString::fromUtf8("load_pushButton"));

        horizontalLayout->addWidget(load_pushButton);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        jsonOutput_radioButton = new QRadioButton(widget);
        jsonOutput_radioButton->setObjectName(QString::fromUtf8("jsonOutput_radioButton"));
        jsonOutput_radioButton->setChecked(false);

        verticalLayout_2->addWidget(jsonOutput_radioButton);

        configOutput_radioButton = new QRadioButton(widget);
        configOutput_radioButton->setObjectName(QString::fromUtf8("configOutput_radioButton"));
        configOutput_radioButton->setChecked(true);

        verticalLayout_2->addWidget(configOutput_radioButton);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addOption_pushButton = new QPushButton(widget);
        addOption_pushButton->setObjectName(QString::fromUtf8("addOption_pushButton"));

        verticalLayout->addWidget(addOption_pushButton);

        editOption_pushButton = new QPushButton(widget);
        editOption_pushButton->setObjectName(QString::fromUtf8("editOption_pushButton"));

        verticalLayout->addWidget(editOption_pushButton);

        removeOption_pushButton = new QPushButton(widget);
        removeOption_pushButton->setObjectName(QString::fromUtf8("removeOption_pushButton"));

        verticalLayout->addWidget(removeOption_pushButton);


        gridLayout_2->addLayout(verticalLayout, 0, 2, 2, 1);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 10));
        progressBar->setMaximumSize(QSize(16777215, 10));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        gridLayout_2->addWidget(progressBar, 2, 1, 1, 2);


        gridLayout->addWidget(widget, 1, 2, 1, 1);

        configFile_treeView = new QTreeView(centralwidget);
        configFile_treeView->setObjectName(QString::fromUtf8("configFile_treeView"));
        configFile_treeView->setMinimumSize(QSize(350, 400));

        gridLayout->addWidget(configFile_treeView, 0, 0, 1, 2);

        listWidget = new QListWidget(centralwidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 803, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        save_pushButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        load_pushButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        jsonOutput_radioButton->setText(QCoreApplication::translate("MainWindow", "JSON", nullptr));
        configOutput_radioButton->setText(QCoreApplication::translate("MainWindow", "Config", nullptr));
        addOption_pushButton->setText(QCoreApplication::translate("MainWindow", "Add option", nullptr));
        editOption_pushButton->setText(QCoreApplication::translate("MainWindow", "Edit option", nullptr));
        removeOption_pushButton->setText(QCoreApplication::translate("MainWindow", "Remove option", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "Option 1 : UNDEFINED", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "Option 2 : UNDEFINED", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
