#include "Window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	//connect(ui.btEgal,SIGNAL(clicked()),this,SLOT(calcul()));
}
