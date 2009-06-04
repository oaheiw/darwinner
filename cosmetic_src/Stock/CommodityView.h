#ifndef CommodityView_H
#define CommodityView_H

#include "common.h"
#include "ItemView.h"
class Business;

class CommodityView : public ItemView
{
public:
	CommodityView(/*int row,*/ QWidget *parent = 0);
	~CommodityView();
	void addBusiness(Business& data);
	
private:
	ArrayUint32String* m_businessTypeNames;
};

#endif // CommodityView_H
