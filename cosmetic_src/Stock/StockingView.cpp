///////////////////////////////////////////////////////////
//  StockingView.cpp
//  Implementation of the Class StockingView
//  Created on:      15-ÁùÔÂ-2009 16:59:11
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "StockingView.h"
#include "Stock.h"
#include <QSortFilterProxyModel>
#include "common.h"
#include "AnythingFactory.h"
#include "UiStrings.h"

StockingView::StockingView(QWidget *parent)
:ItemView(parent, ItemView::SIMPLEVIEW_DATEBOX)
{
	setButtonsVisable(true);
	m_directionNames = AnythingFactory<ArrayUint32String>::instance()->
		createAnything(STOCKDIRECTION);	
	(*m_directionNames)[STOCKING_IN] = stockInStr;
	(*m_directionNames)[STOCKING_OUT] = stockOutStr;

	QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
	setProxy(proxy);
	appendColumn(6);
	setTitle(LOCAL8BITSTR(stStockStr));
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR(stStockIdStr));
	setHeaderData(col++, LOCAL8BITSTR(stDirectionStr));
	setHeaderData(col++, LOCAL8BITSTR(stAmountStr));
	setHeaderData(col++, LOCAL8BITSTR(stUintPriceStr));
	setHeaderData(col++, LOCAL8BITSTR(stTotalPriceStr));
	setHeaderData(col++, LOCAL8BITSTR(stStockDateStr));

	setAutoResize(true);
}


StockingView::~StockingView(){

}





void StockingView::addStocking(Stock& data){
	int col = 0;
	addData(0, col++, data.getId());
	addData(0, col++, LOCAL8BITSTR((*m_directionNames)[data.getDirction()].c_str()));
	addData(0, col++, data.getAmount());
	addData(0, col++, data.getUnitPrice());
	addData(0, col++, data.getDate().c_str());
	
}