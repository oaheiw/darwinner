#ifndef BUSINESSITEMVIEW_H
#define BUSINESSITEMVIEW_H

#include "ItemView.h"

class BusinessItemView : public ItemView
{
public:
	BusinessItemView(/*int row,*/ QWidget *parent = 0);
	~BusinessItemView();

private:
	/*int m_column;*/
};

#endif // BUSINESSITEMVIEW_H
