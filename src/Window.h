#include <QtGui>
#include <QtGui/QWidget>
#include <QFileDialog>

#include "ui_untitled.h"

class Window : public QMainWindow
{
    Q_OBJECT

    private slots:
    	//void calcul() const;

public:
    Window(QWidget *parent = 0);
	~Window() {};

private:
    Ui::MainWindow ui;
	QDir InputFile;
	QDir OutputFile;
	void connectActions();


private slots:
	void changeInFile();
	void changeOutFile();
	void UpdateInputPath();
	void UpdateOutputPath();
	void DoStuff();
};
