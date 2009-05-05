#ifndef BUSINESSITEMVIEW_H
#define BUSINESSITEMVIEW_H

#include "ItemView.h"
class Business;

class BusinessItemView : public ItemView
{
public:
	BusinessItemView(/*int row,*/ QWidget *parent = 0);
	~BusinessItemView();
	void addBusiness(Business& data);
};

#endif // BUSINESSITEMVIEW_H
