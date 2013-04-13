#include "adt.h"
#include "tools.h"
//#include "debuglog.h"
#include <QApplication>

#include "Window.h"

using namespace std;

int main(int argc, char* argv[])
{
	//copyMCLQ(argc, argv);
	//allWater(argc, argv);
	QApplication app(argc, argv);
	Window w;
	w.show();
    return app.exec();

	//Rewrite(argc, argv);
}