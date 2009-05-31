///////////////////////////////////////////////////////////
//  CustomerListView.h
//  Implementation of the Class CustomerListView
//  Created on:      30-ÎåÔÂ-2009 21:19:06
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_FED78DC8_8A88_4176_BB25_C083BB1B4CD1__INCLUDED_)
#define EA_FED78DC8_8A88_4176_BB25_C083BB1B4CD1__INCLUDED_

#include "ItemView.h"
#include "common.h"
class Customer;

class CustomerListView : public ItemView
{

public:
	CustomerListView(QWidget *parent = 0);
	virtual ~CustomerListView();

	void addCustomer(Customer& data);

private:
	ArrayUint32String* m_customerLevelNames;

};
#endif // !defined(EA_FED78DC8_8A88_4176_BB25_C083BB1B4CD1__INCLUDED_)
