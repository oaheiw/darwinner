#ifndef BUSINESSWINDOW_H
#define BUSINESSWINDOW_H

#include <QMainWindow>
#include "ui_BusinessWindow.h"

class BusinessWindow : public QMainWindow
{
	Q_OBJECT

public:
	BusinessWindow(QWidget *parent = 0);
	~BusinessWindow();

private:
	Ui::BusinessWindowClass ui;
};

#endif // BUSINESSWINDOW_H
