#include <QtGui>
#include <QWidget>
#include <QFileDialog>

#include "ui_MainWindows.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private slots:
    	//void calcul() const;

public:
    MainWindow(QWidget *parent = 0);
	~MainWindow() {};

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
