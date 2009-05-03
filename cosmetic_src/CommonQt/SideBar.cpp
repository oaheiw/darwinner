#include "common.h"
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
		ui.hideButton->setStatusTip(LOCAL8BITSTR(expandSideBarStr));
		ui.hideButton->setToolTip(LOCAL8BITSTR(expandSideBarStr));
		for(list<QWidget*>::iterator it = widgetList.begin() ; widgetList.end() != it ; it++)
			(*it)->close();
	} else {
		ui.hideButton->setText(">");
		ui.hideButton->setStatusTip(LOCAL8BITSTR(shrinkSideBarStr));
		ui.hideButton->setToolTip(LOCAL8BITSTR(shrinkSideBarStr));
		for(list<QWidget*>::iterator it = widgetList.begin() ; widgetList.end() != it ; it++)
			(*it)->show();
	}
}

