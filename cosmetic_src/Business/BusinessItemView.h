#ifndef BUSINESSITEMVIEW_H
#define BUSINESSITEMVIEW_H

#include "ItemView.h"
#include "Business.h"
#include <list>
using namespace std;

class BusinessItemView : public ItemView
{
public:
	BusinessItemView(/*int row,*/ QWidget *parent = 0);
	~BusinessItemView();
	void addBusiness(list<Business> data);
};

#endif // BUSINESSITEMVIEW_H
