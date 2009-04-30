#include "BusinessItemView.h"
#include <QSortFilterProxyModel>

BusinessItemView::BusinessItemView(/*int column,*/ QWidget *parent)
//:m_column(column)
:ItemView(/*m_column,*/ parent)
{
	initDataModel(5);
	QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
	setProxy(proxy);
}

BusinessItemView::~BusinessItemView()
{

}
