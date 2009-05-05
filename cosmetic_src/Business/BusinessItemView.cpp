#include "BusinessItemView.h"
#include <QSortFilterProxyModel>
#include "common.h"
#include "UiStrings.h"
#include "Business.h"
using namespace UiStr;

extern StringArray g_businessTypeNames;

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
	setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmNameStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmBrandStr));
	setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmRatingStr));
	setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(UiStr::bmSpecificationStr));
	setColumnWidth(col, 70);
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

void BusinessItemView::addBusiness(Business& data)
{
	int col = 0;
	addData(0, col++, data.id());
	addData(0, col++, LOCAL8BITSTR(g_businessTypeNames[data.type()].c_str()));
	addData(0, col++, LOCAL8BITSTR(data.name().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.brand().c_str()));
	addData(0, col++, data.getRating());
	addData(0, col++, LOCAL8BITSTR(data.specification().c_str()));
	addData(0, col++, data.price());
	addData(0, col++, data.discount());
	addData(0, col++, LOCAL8BITSTR(data.description().c_str()));
	addData(0, col++, data.buys());
	addData(0, col++, data.sales());
	addData(0, col++, data.stocks());
}

