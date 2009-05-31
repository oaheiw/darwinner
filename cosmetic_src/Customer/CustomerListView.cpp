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
#include "Singleton.h"


CustomerListView::CustomerListView(QWidget *parent)
:ItemView(parent){
	setTitle(LOCAL8BITSTR(cmCustomerBrowseStr));
}



CustomerListView::~CustomerListView(){

}





void CustomerListView::addCustomer(Customer& data){

}