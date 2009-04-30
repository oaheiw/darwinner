#include "SideBar.h"

SideBar::SideBar(QWidget *parent)
	: QWidget(parent)
{
	widgetList.clear();
	ui.setupUi(this);
}

SideBar::~SideBar()
{

}

void SideBar::addWidget(QWidget *widget, int x, int y, int row, int column)
{
	ui.gridLayout->addWidget(widget, x, y, row, column);
	widgetList.push_back(widget);
}

void SideBar::hideWidget(bool hide)
{
	if(hide) {
		ui.hideButton->setText("<");
		for(list<QWidget*>::iterator it = widgetList.begin() ; widgetList.end() != it ; it++)
			(*it)->close();
	} else {
		ui.hideButton->setText(">");
		for(list<QWidget*>::iterator it = widgetList.begin() ; widgetList.end() != it ; it++)
			(*it)->show();
	}
}

