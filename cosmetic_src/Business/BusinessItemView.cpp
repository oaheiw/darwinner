#include "BusinessItemView.h"
#include <QSortFilterProxyModel>
#include "common.h"
#include "UiStrings.h"
#include "Business.h"
#include "AnythingFactory.h"
#include "Singleton.h"
#include "ProgressBarDelegate.h"

BusinessItemView::BusinessItemView(QWidget *parent)
:ItemView(parent)
{
	setButtonsVisable(true);
	m_businessTypeNames = AnythingFactory<ArrayUint32String>::instance()->createAnything(BUSINESSTYPE);	

	QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
	setProxy(proxy);
	appendColumn(12);
	setTitle(LOCAL8BITSTR(bmBrowseStr));
	int col = 0;
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(bmIdStr));
	//setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(bmTypeStr));
	//setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(bmNameStr));
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(bmBrandStr));
	//setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(bmSpecificationStr));
	//setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(bmRatingStr));
	//setColumnWidth(col, 70);
	setHeaderData(col++, LOCAL8BITSTR(bmPriceStr));
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(bmDiscountStr));
	//setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(bmDescriptionStr));
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(bmBuysStr));
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(bmSalesStr));
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(bmStocksStr));

	ProgressBarDelegate *delegateRating = new ProgressBarDelegate(this);
	delegateRating->setFormat(LOCAL8BITSTR("%v/%m"));
	delegateRating->setRange(0 , 100);
	setDelegate(5, delegateRating);
}

BusinessItemView::~BusinessItemView()
{

}

void BusinessItemView::addBusiness(Business& data)
{
	int col = 0;
	addData(0, col++, data.id());
	addData(0, col++, LOCAL8BITSTR((*m_businessTypeNames)[data.type()].c_str()));
	addData(0, col++, LOCAL8BITSTR(data.name().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.brand().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.specification().c_str()));
	addData(0, col++, data.getRating());
	addData(0, col++, data.price());
	addData(0, col++, data.discount());
	addData(0, col++, LOCAL8BITSTR(data.description().c_str()));
	addData(0, col++, data.buys());
	addData(0, col++, data.sales());
	addData(0, col++, data.stocks());
}

