///////////////////////////////////////////////////////////
//  Inventory.h
//  Implementation of the Class Inventory
//  Created on:      03-ÁùÔÂ-2009 12:10:37
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_4F2321E1_83F1_4818_ABE5_B9F622B3AB3F__INCLUDED_)
#define EA_4F2321E1_83F1_4818_ABE5_B9F622B3AB3F__INCLUDED_

#include "common.h"

class Inventory
{

public:
	Inventory();
	virtual ~Inventory();

	uint64 getActualInventory();
	uint64 getCalculatedInventory();
	string getDate();
	uint32 getId();
	uint32 getSalesId();
	void setActualInventory(uint64 newVal);
	void setCalculatedInventory(uint64 newVal);
	void setDate(string newVal);
	void setId(uint32 newVal);
	void setSalesId(uint32 newVal);

private:
	uint64 m_actualInventory;
	uint64 m_calculatedInventory;
	string m_date;
	uint32 m_id;
	uint32 m_salesId;

};
#endif // !defined(EA_4F2321E1_83F1_4818_ABE5_B9F622B3AB3F__INCLUDED_)
