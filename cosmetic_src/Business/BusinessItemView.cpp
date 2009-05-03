#include "BusinessItemView.h"
#include <QSortFilterProxyModel>

BusinessItemView::BusinessItemView(/*int column,*/ QWidget *parent)
//:m_column(column)
:ItemView(/*m_column,*/ parent)
{
	QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
	setProxy(proxy);
}

BusinessItemView::~BusinessItemView()
{

}
