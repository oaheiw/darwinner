#include "BusinessItemView.h"
#include <QSortFilterProxyModel>
#include "UiStrings.h"
using namespace UiStr;

BusinessItemView::BusinessItemView(QWidget *parent)
:ItemView(parent)
{
	QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
	setProxy(proxy);
	appendColumn(12);
	setTitle(LOCAL8BITSTR(bmBrowseStr));
	int col = 0;
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmIdStr));
	setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmTypeStr));
	setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmNameStr));
	setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmBrandStr));
	setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmRatingStr));
	setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmSpecificationStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmPriceStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmDiscountStr));
	setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmDescriptionStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmBuysStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmSalesStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmStocksStr));
}

BusinessItemView::~BusinessItemView()
{

}

void BusinessItemView::addBusiness(list<Business> data)
{

}

