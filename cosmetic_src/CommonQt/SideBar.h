#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include "ui_SideBar.h"
#include <list>
using namespace std;

class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar(QWidget *parent = 0);
	~SideBar();
	void addWidget(QWidget *widget, int x, int y, int row = 1, int column = 1);

private:
	list<QWidget*> widgetList;
	Ui::SideBarClass ui;

private slots:
	void hideWidget(bool hide);
};

#endif // SIDEBAR_H
