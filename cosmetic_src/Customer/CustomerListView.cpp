///////////////////////////////////////////////////////////
//  CustomerListView.cpp
//  Implementation of the Class CustomerListView
//  Created on:      30-ÎåÔÂ-2009 21:19:06
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "CustomerListView.h"
#include <QSortFilterProxyModel>
#include "common.h"
#include "UiStrings.h"
#include "Customer.h"
#include "AnythingFactory.h"


CustomerListView::CustomerListView(QWidget *parent)
:ItemView(parent){
	setButtonsVisable(true);
	setTitle(LOCAL8BITSTR(cmCustomerBrowseStr));

	m_customerLevelNames = AnythingFactory<ArrayUint32String>::
		instance()->createAnything(CUSTOMERLEVEL);
	m_sexNames = AnythingFactory<ArrayUint32String>::
		instance()->createAnything(SEXNAMES);

	QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
	setProxy(proxy);

	appendColumn(11);

	int col = 0;
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(cmIdStr));
	//setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(cmNameStr));
	//setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(cmSexStr));
	//setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(cmLevelStr));
	//setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(cmCellStr));
	//setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(cmPhoneStr));
	//setColumnWidth(col, 120);
	setHeaderData(col++, LOCAL8BITSTR(cmConsumeTimesStr));
	//setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(cmTotalConsumeStr));
	//setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(cmDepositStr));
	//setColumnWidth(col, 200);
	setHeaderData(col++, LOCAL8BITSTR(cmAddressStr));
	//setColumnWidth(col, 200);
	setHeaderData(col++, LOCAL8BITSTR(cmDescriptionStr));
}



CustomerListView::~CustomerListView(){

}





void CustomerListView::addCustomer(Customer& data){
	int col = 0;
	addData(0, col++, data.id());
	addData(0, col++, LOCAL8BITSTR(data.name().c_str()));
	addData(0, col++, LOCAL8BITSTR((*m_sexNames)[data.sex()].c_str()));
	addData(0, col++, LOCAL8BITSTR((*m_customerLevelNames)[data.getLevel()].c_str()));
	addData(0, col++, LOCAL8BITSTR(data.cell().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.phone().c_str()));
	addData(0, col++, data.getConsumeTime());
	addData(0, col++, data.getTotalConsume());
	addData(0, col++, data.getDeposit());
	addData(0, col++, LOCAL8BITSTR(data.address().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.description().c_str()));
}