#include "MainWindow.h"
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) 
{
	ui.setupUi(this);
	connectActions();
}

void MainWindow::connectActions() 
{
	connect(ui.action_Quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
	connect(ui.toolButton_browse_Input, SIGNAL(clicked()), this, SLOT(changeInFile()));
	connect(ui.toolButton_browse_Output, SIGNAL(clicked()), this, SLOT(changeOutFile()));
	connect(ui.lineEdit_Input, SIGNAL(editingFinished()), this, SLOT(UpdateInputPath()));
	connect(ui.lineEdit_Output, SIGNAL(editingFinished()), this, SLOT(UpdateOutputPath()));
	connect(ui.pushButton, SIGNAL(released()), this, SLOT(DoStuff()));
}

void MainWindow::changeInFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Input File"), InputFile.path(), tr("ADT (*.adt);;All files (*.*)"));
    if (!path.isNull())
    {
        InputFile.setPath(path);
		ui.lineEdit_Input->setText(path);
    }
}

void MainWindow::changeOutFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Ouput File"), OutputFile.path(), tr("ADT (*.adt);;All files (*.*)"));
    if (!path.isNull())
    {
        OutputFile.setPath(path);
		ui.lineEdit_Output->setText(path);
    }
}

void MainWindow::UpdateInputPath() 
{
	std::cout << "UpdateInputPath() " << ui.lineEdit_Input->text().toStdString() << std::endl;
	InputFile.setPath(ui.lineEdit_Input->text());
}

void MainWindow::UpdateOutputPath()
{
	std::cout << "UpdateOutputPath() "  << ui.lineEdit_Output->text().toStdString() << std::endl;
	OutputFile.setPath(ui.lineEdit_Output->text());
}

void MainWindow::DoStuff()
{
	std::string In = InputFile.path().toStdString();
	std::string Out = OutputFile.path().toStdString();
	char** argv = new char*[3];
	argv[0] = " ";
	argv[1] = (char*)Out.c_str();
	argv[2] = (char*)In.c_str();
	//copyMCLQ(3, argv);
}