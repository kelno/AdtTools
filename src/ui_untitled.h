/********************************************************************************
** Form generated from reading UI file 'untitled.ui'
**
** Created: Sat 13. Apr 09:32:43 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UNTITLED_H
#define UNTITLED_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
    QWidget *widget;
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
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(470, 130);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        action_Close->setEnabled(false);
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Hohi = new QAction(MainWindow);
        action_Hohi->setObjectName(QString::fromUtf8("action_Hohi"));
        actionTic = new QAction(MainWindow);
        actionTic->setObjectName(QString::fromUtf8("actionTic"));
        actionTic->setCheckable(true);
        actionTic->setChecked(true);
        actionTac = new QAction(MainWindow);
        actionTac->setObjectName(QString::fromUtf8("actionTac"));
        actionTac->setCheckable(true);
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 70, 75, 23));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 451, 50));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_Input = new QLabel(widget);
        label_Input->setObjectName(QString::fromUtf8("label_Input"));

        verticalLayout_3->addWidget(label_Input);

        label_Output = new QLabel(widget);
        label_Output->setObjectName(QString::fromUtf8("label_Output"));

        verticalLayout_3->addWidget(label_Output);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_Input = new QLineEdit(widget);
        lineEdit_Input->setObjectName(QString::fromUtf8("lineEdit_Input"));
        lineEdit_Input->setEnabled(true);

        verticalLayout->addWidget(lineEdit_Input);

        lineEdit_Output = new QLineEdit(widget);
        lineEdit_Output->setObjectName(QString::fromUtf8("lineEdit_Output"));
        lineEdit_Output->setEnabled(true);

        verticalLayout->addWidget(lineEdit_Output);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButton_browse_Input = new QToolButton(widget);
        toolButton_browse_Input->setObjectName(QString::fromUtf8("toolButton_browse_Input"));

        verticalLayout_2->addWidget(toolButton_browse_Input);

        toolButton_browse_Output = new QToolButton(widget);
        toolButton_browse_Output->setObjectName(QString::fromUtf8("toolButton_browse_Output"));

        verticalLayout_2->addWidget(toolButton_browse_Output);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 470, 19));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Close->setText(QApplication::translate("MainWindow", "&Close", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Hohi->setText(QApplication::translate("MainWindow", "&Hohi", 0, QApplication::UnicodeUTF8));
        actionTic->setText(QApplication::translate("MainWindow", "Tic", 0, QApplication::UnicodeUTF8));
        actionTac->setText(QApplication::translate("MainWindow", "Tac", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Do Stuff !", 0, QApplication::UnicodeUTF8));
        label_Input->setText(QApplication::translate("MainWindow", "Input File", 0, QApplication::UnicodeUTF8));
        label_Output->setText(QApplication::translate("MainWindow", "Output File", 0, QApplication::UnicodeUTF8));
        toolButton_browse_Input->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_browse_Output->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UNTITLED_H
