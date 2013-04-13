#include <QtGui>
#include <QtGui/QWidget>

#include "ui_untitled.h"

class Window : public QWidget
{
    Q_OBJECT

    private slots:
    	//void calcul() const;

public:
    Window(QWidget *parent = 0);
	~Window() {};

private:
    Ui::Form ui;
};
