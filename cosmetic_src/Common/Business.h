///////////////////////////////////////////////////////////
//  Business.h
//  Implementation of the Class Business
//  Created on:      02-ÎåÔÂ-2009 22:33:25
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_F40DCE33_D8D3_43b0_ABAF_0743D8FE2008__INCLUDED_)
#define EA_F40DCE33_D8D3_43b0_ABAF_0743D8FE2008__INCLUDED_

#include "common.h"
#include <string>
using namespace std;

class Business
{

public:
	Business();
	virtual ~Business();

	string& brand();
	uint32 buys();
	uint32 cost();
	string& description();
	short discount();
	uint32 id();
	string& name();
	uint32 price();
	uint32 sales();
	void setBrand(string brand);
	void setBuys(uint32 buys);
	void setCost(uint32 cost);
	void setDescription(string description);
	void setDiscount(short discount);
	void setId(uint32 id);
	void setName(string name);
	void setPrice(uint32 price);
	void setSales(uint32 sales);
	void setSpecification(string specification);
	void setStocks(uint32 stocks);
	void setType(uint32 type);
	string& specification();
	uint32 stocks();
	uint32 type();

private:
	string m_brand;
	uint32 m_buys;
	uint32 m_cost;
	string m_description;
	uint32 m_discount;
	uint32 m_id;
	string m_name;
	uint32 m_price;
	uint32 m_sales;
	string m_specification;
	uint32 m_stocks;
	uint32 m_type;

};
#endif // !defined(EA_F40DCE33_D8D3_43b0_ABAF_0743D8FE2008__INCLUDED_)
