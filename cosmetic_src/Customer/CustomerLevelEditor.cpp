///////////////////////////////////////////////////////////
//  CustomerLevelEditor.cpp
//  Implementation of the Class CustomerLevelEditor
//  Created on:      31-ÎåÔÂ-2009 22:04:57
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "CustomerLevelEditor.h"
#include "CustomerLevel.h"
//#include "common.h"
#include "CustomerLevel.h"
#include <list>
#include "UiStrings.h"
#include "SpinBoxDelegate.h"
#include <limits>
using namespace std;

CustomerLevelEditor::CustomerLevelEditor(QWidget *parent)
:ItemEditor(parent){
	appendColumn(5);
	setWindowTitle(LOCAL8BITSTR(cmLevelEditorStr));
	setTitle(LOCAL8BITSTR(emptyStr));
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR(cmLevelIdStr));
	setHeaderData(col++, LOCAL8BITSTR(cmLevelNameStr));
	setHeaderData(col++, LOCAL8BITSTR(cmLevelRequireStr));
	setHeaderData(col++, LOCAL8BITSTR(cmLevelDiscountStr));
	setHeaderData(col++, LOCAL8BITSTR(cmLevelDescriptionStr));

	m_requireDelegate = new SpinBoxDelegate(this);
	m_requireDelegate->setRange(0, numeric_limits<int>::max());
	m_requireDelegate->setPrefix(moneyStr);
	setDelegate(2, m_requireDelegate);

	m_discountDelegate = new SpinBoxDelegate(this);
	m_discountDelegate->setRange(0, 100);
	m_discountDelegate->setSuffix(percentStr);
	setDelegate(3, m_discountDelegate);
}



CustomerLevelEditor::~CustomerLevelEditor(){

}





void* CustomerLevelEditor::getData(){
	list<CustomerLevel>* data = new list<CustomerLevel>;
	for (int row=0; row < m_DataModel->rowCount(); row++)
	{	
		CustomerLevel temp;
		int col=0;
		temp.setId(m_DataModel->index(row, col++).data().toUInt());
		temp.setName(string(m_DataModel->index(row, col++).data()
			.toString().toLocal8Bit().data()));
		if(temp.getName().empty()) continue;// ignore item with empty name
		temp.setTotalCosume(m_DataModel->index(row, col++).data().toULongLong());
		temp.setDiscount(m_DataModel->index(row, col++).data().toUInt());
		temp.setDescription(string(m_DataModel->index(row, col++).data()
			.toString().toLocal8Bit().data()));
		data->push_back(temp);
	}
	return data;
}

void CustomerLevelEditor::addCustomerLevel(const CustomerLevel & data)
{
	int col = 0;
	addData(0, col++, data.getId());
	addData(0, col++, LOCAL8BITSTR(data.getName().c_str()));
	addData(0, col++, data.getTotalCosume());
	addData(0, col++, data.getDiscount());
	addData(0, col++, LOCAL8BITSTR(data.getDescription().c_str()));
}

void CustomerLevelEditor::addCustomerLevel(const list<CustomerLevel>* data)
{
	for(list<CustomerLevel>::const_iterator it = data->begin() ; 
		data->end() != it ; it++ )
		addCustomerLevel(*it);
}