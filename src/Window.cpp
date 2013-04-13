#include "Window.h"
#include "tools.h"
#include <string>

Window::Window(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	connectActions();
}

void Window::connectActions() {
	connect(ui.action_Quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
	connect(ui.toolButton_browse_Input, SIGNAL(clicked()), this, SLOT(changeInFile()));
	connect(ui.toolButton_browse_Output, SIGNAL(clicked()), this, SLOT(changeOutFile()));
	connect(ui.lineEdit_Input, SIGNAL(editingFinished()), this, SLOT(UpdateInputPath()));
	connect(ui.lineEdit_Output, SIGNAL(editingFinished()), this, SLOT(UpdateOutputPath()));
	connect(ui.pushButton, SIGNAL(released()), this, SLOT(DoStuff()));
}

void Window::changeInFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Input File"), InputFile.path(), tr("ADT (*.adt);;All files (*.*)"));
    if (!path.isNull())
    {
        InputFile.setPath(path);
		ui.lineEdit_Input->setText(path);
    }
}

void Window::changeOutFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Ouput File"), OutputFile.path(), tr("ADT (*.adt);;All files (*.*)"));
    if (!path.isNull())
    {
        OutputFile.setPath(path);
		ui.lineEdit_Output->setText(path);
    }
}

void Window::UpdateInputPath() 
{
	std::cout << "UpdateInputPath() " << ui.lineEdit_Input->text().toStdString() << std::endl;
	InputFile.setPath(ui.lineEdit_Input->text());
}

void Window::UpdateOutputPath()
{
	std::cout << "UpdateOutputPath() "  << ui.lineEdit_Output->text().toStdString() << std::endl;
	OutputFile.setPath(ui.lineEdit_Output->text());
}

void Window::DoStuff()
{
	std::string In = InputFile.path().toStdString();
	std::string Out = OutputFile.path().toStdString();
	char** argv = new char*[3];
	argv[0] = " ";
	argv[1] = (char*)Out.c_str();
	argv[2] = (char*)In.c_str();
	copyMCLQ(3, argv);
}