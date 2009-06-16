///////////////////////////////////////////////////////////
//  InventoryView.cpp
//  Implementation of the Class InventoryView
//  Created on:      15-ÁùÔÂ-2009 16:59:13
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "InventoryView.h"
#include "Inventory.h"
#include <QSortFilterProxyModel>
#include "common.h"
#include "UiStrings.h"


InventoryView::InventoryView(QWidget *parent)
:ItemView(parent, ItemView::SIMPLEVIEW_DATEBOX)
{
	setButtonsVisable(true);
	QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
	setProxy(proxy);
	appendColumn(6);
	setTitle(LOCAL8BITSTR(stInventoryStr));
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR(stInventoryIdStr));
	setHeaderData(col++, LOCAL8BITSTR(stActualInventoryStr));
	setHeaderData(col++, LOCAL8BITSTR(stCalculatedInventoryStr));
	setHeaderData(col++, LOCAL8BITSTR(stInventroyDiffStr));
	setHeaderData(col++, LOCAL8BITSTR(stCheckingStartDateStr));
	setHeaderData(col++, LOCAL8BITSTR(stCheckingFinishDateStr));

	setAutoResize(true);
}



InventoryView::~InventoryView(){

}





void InventoryView::addInventory(Inventory& data){
	int col = 0;
	addData(0, col++, data.getId());
	addData(0, col++, data.getActualInventory());
	addData(0, col++, data.getCalculatedInventory());
	addData(0, col++, data.getDifference());
	addData(0, col++, data.getDate().c_str());
}