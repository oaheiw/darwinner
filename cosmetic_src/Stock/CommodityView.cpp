#include "CommodityView.h"
#include <QSortFilterProxyModel>
#include "common.h"
#include "UiStrings.h"
#include "Business.h"
#include "AnythingFactory.h"
#include "Singleton.h"
#include "ProgressBarDelegate.h"

CommodityView::CommodityView(QWidget *parent)
:ItemView(parent)
{
	m_businessTypeNames = AnythingFactory<ArrayUint32String>::instance()->createAnything(BUSINESSTYPE);	

	QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
	setProxy(proxy);
	appendColumn(12);
	setTitle(LOCAL8BITSTR(stCommodityStr));
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR(stIdStr));
	setHeaderData(col++, LOCAL8BITSTR(stTypeStr));
	setHeaderData(col++, LOCAL8BITSTR(stNameStr));
	setHeaderData(col++, LOCAL8BITSTR(stBrandStr));
	setHeaderData(col++, LOCAL8BITSTR(stRatingStr));
	setHeaderData(col++, LOCAL8BITSTR(stDescriptionStr));
	setHeaderData(col++, LOCAL8BITSTR(stBuysStr));
	setHeaderData(col++, LOCAL8BITSTR(stAverageCostStr));
	setHeaderData(col++, LOCAL8BITSTR(stCostsStr));
	setHeaderData(col++, LOCAL8BITSTR(stStocksStr));
	setHeaderData(col++, LOCAL8BITSTR(stDiscountStr));
	setHeaderData(col++, LOCAL8BITSTR(stPriceStr));
	setHeaderData(col++, LOCAL8BITSTR(stSalesStr));
	setHeaderData(col++, LOCAL8BITSTR(stSalesSumStr));
	setHeaderData(col++, LOCAL8BITSTR(stAveragePriceStr));
	setHeaderData(col++, LOCAL8BITSTR(stSpecificationStr));


	ProgressBarDelegate *delegateRating = new ProgressBarDelegate(this);
	delegateRating->setFormat(LOCAL8BITSTR("%v/%m"));
	delegateRating->setRange(0 , 100);
	setDelegate(5, delegateRating);
}

CommodityView::~CommodityView()
{

}

void CommodityView::addBusiness(Business& data)
{
	int col = 0;
	addData(0, col++, data.id());
	addData(0, col++, LOCAL8BITSTR((*m_businessTypeNames)[data.type()].c_str()));
	addData(0, col++, LOCAL8BITSTR(data.name().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.brand().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.specification().c_str()));
	addData(0, col++, data.getRating());
	addData(0, col++, data.buys());
	addData(0, col++, data.cost());
	addData(0, col++, data.cost()*data.buys());
	addData(0, col++, data.stocks());
	addData(0, col++, data.discount());
	addData(0, col++, data.price());
	addData(0, col++, data.sales());
	addData(0, col++, data.getSaleSum());
	addData(0, col++, data.getSaleSum()/data.sales());
	addData(0, col++, LOCAL8BITSTR(data.description().c_str()));
}

