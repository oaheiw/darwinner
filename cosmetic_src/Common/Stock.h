///////////////////////////////////////////////////////////
//  Stock.h
//  Implementation of the Class Stock
//  Created on:      03-ÁùÔÂ-2009 12:10:40
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_863C5A5D_BF26_4183_AAB7_6C9D2A3A22E4__INCLUDED_)
#define EA_863C5A5D_BF26_4183_AAB7_6C9D2A3A22E4__INCLUDED_

#include "common.h"

class Stock
{

public:
	Stock();
	virtual ~Stock();

	uint64 getAmount();
	short getDirction();
	uint64 getId();
	uint32 getSalesId();
	string getStockingDate();
	double32 getUnitPrice();
	void setAmount(uint64 newVal);
	void setDirction(short newVal);
	void setId(uint64 newVal);
	void setSalesId(uint32 newVal);
	void setStockingDate(string newVal);
	void setUnitPrice(double32 newVal);

private:
	uint64 m_amount;
	short m_dirction;
	uint64 m_id;
	uint32 m_salesId;
	string m_stockingDate;
	double32 m_unitPrice;

};
#endif // !defined(EA_863C5A5D_BF26_4183_AAB7_6C9D2A3A22E4__INCLUDED_)
