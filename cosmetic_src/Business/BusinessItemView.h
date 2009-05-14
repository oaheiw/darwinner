#ifndef BUSINESSITEMVIEW_H
#define BUSINESSITEMVIEW_H

#include "common.h"
#include "ItemView.h"
class Business;

class BusinessItemView : public ItemView
{
public:
	BusinessItemView(/*int row,*/ QWidget *parent = 0);
	~BusinessItemView();
	void addBusiness(Business& data);
	
private:
	ArrayUint32String* m_businessTypeNames;
};

#endif // BUSINESSITEMVIEW_H
