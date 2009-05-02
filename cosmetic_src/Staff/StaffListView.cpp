#include "StaffListView.h"
#include <QSortFilterProxyModel>

StaffListView::StaffListView(QWidget *parent)
: ItemView(parent)
{

}

StaffListView::~StaffListView()
{

}

void StaffListView::init(int col, QSortFilterProxyModel* proxy)
{
	setTitle(QString::fromLocal8Bit("‘±π§‰Ø¿¿"));
	initDataModel(col);
	if(NULL == proxy)
		proxy = new QSortFilterProxyModel();//default proxy
	setProxy(proxy);
}
