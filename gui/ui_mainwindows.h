/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Close;
    QAction *action_Quit;
    QAction *action_Hohi;
    QAction *actionTic;
    QAction *actionTac;
    QAction *action_About;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_Input;
    QLabel *label_Output;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_Input;
    QLineEdit *lineEdit_Output;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButton_browse_Input;
    QToolButton *toolButton_browse_Output;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_Help;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(475, 136);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QStringLiteral("action_Close"));
        action_Close->setEnabled(false);
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Hohi = new QAction(MainWindow);
        action_Hohi->setObjectName(QStringLiteral("action_Hohi"));
        actionTic = new QAction(MainWindow);
        actionTic->setObjectName(QStringLiteral("actionTic"));
        actionTic->setCheckable(true);
        actionTic->setChecked(true);
        actionTac = new QAction(MainWindow);
        actionTac->setObjectName(QStringLiteral("actionTac"));
        actionTac->setCheckable(true);
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QStringLiteral("action_About"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 70, 75, 23));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 451, 50));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_Input = new QLabel(layoutWidget);
        label_Input->setObjectName(QStringLiteral("label_Input"));

        verticalLayout_3->addWidget(label_Input);

        label_Output = new QLabel(layoutWidget);
        label_Output->setObjectName(QStringLiteral("label_Output"));

        verticalLayout_3->addWidget(label_Output);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit_Input = new QLineEdit(layoutWidget);
        lineEdit_Input->setObjectName(QStringLiteral("lineEdit_Input"));
        lineEdit_Input->setEnabled(true);

        verticalLayout->addWidget(lineEdit_Input);

        lineEdit_Output = new QLineEdit(layoutWidget);
        lineEdit_Output->setObjectName(QStringLiteral("lineEdit_Output"));
        lineEdit_Output->setEnabled(true);

        verticalLayout->addWidget(lineEdit_Output);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        toolButton_browse_Input = new QToolButton(layoutWidget);
        toolButton_browse_Input->setObjectName(QStringLiteral("toolButton_browse_Input"));

        verticalLayout_2->addWidget(toolButton_browse_Input);

        toolButton_browse_Output = new QToolButton(layoutWidget);
        toolButton_browse_Output->setObjectName(QStringLiteral("toolButton_browse_Output"));

        verticalLayout_2->addWidget(toolButton_browse_Output);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 475, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QStringLiteral("menu_Edit"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Close);
        menu_File->addAction(action_Quit);
        menu_Edit->addAction(action_Hohi);
        menu_Edit->addAction(actionTic);
        menu_Edit->addAction(actionTac);
        menu_Help->addAction(action_About);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AdtLib", 0));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
        action_Close->setText(QApplication::translate("MainWindow", "&Close", 0));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        action_Hohi->setText(QApplication::translate("MainWindow", "&Hohi", 0));
        actionTic->setText(QApplication::translate("MainWindow", "Tic", 0));
        actionTac->setText(QApplication::translate("MainWindow", "Tac", 0));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Do Stuff !", 0));
        label_Input->setText(QApplication::translate("MainWindow", "Input File", 0));
        label_Output->setText(QApplication::translate("MainWindow", "Output File", 0));
        toolButton_browse_Input->setText(QApplication::translate("MainWindow", "...", 0));
        toolButton_browse_Output->setText(QApplication::translate("MainWindow", "...", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
