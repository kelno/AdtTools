#include <QtGui>
#include <QWidget>
#include <QFileDialog>
#include <QObject>

#include "ui/ui_MainWindows.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private slots:

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
