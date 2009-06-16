///////////////////////////////////////////////////////////
//  StockingView.h
//  Implementation of the Class StockingView
//  Created on:      15-ÁùÔÂ-2009 16:59:10
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_5E772875_D871_47af_89A9_122C7C4EC0D4__INCLUDED_)
#define EA_5E772875_D871_47af_89A9_122C7C4EC0D4__INCLUDED_

#include "common.h"
#include "ItemView.h"
class Stock;

class StockingView : public ItemView
{

public:
	StockingView(QWidget *parent = 0);
	virtual ~StockingView();

	void addStocking(Stock& data);

private:
	ArrayUint32String* m_directionNames;

};
#endif // !defined(EA_5E772875_D871_47af_89A9_122C7C4EC0D4__INCLUDED_)
