///////////////////////////////////////////////////////////
//  InventoryView.h
//  Implementation of the Class InventoryView
//  Created on:      15-ÁùÔÂ-2009 16:59:12
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_B0AB9475_24F9_45f4_B500_B987AA66A7E8__INCLUDED_)
#define EA_B0AB9475_24F9_45f4_B500_B987AA66A7E8__INCLUDED_

class Inventory;
#include "ItemView.h"

class InventoryView : public ItemView
{

public:
	InventoryView(QWidget *parent = 0);
	virtual ~InventoryView();

	void addInventory(Inventory& data);

};
#endif // !defined(EA_B0AB9475_24F9_45f4_B500_B987AA66A7E8__INCLUDED_)
