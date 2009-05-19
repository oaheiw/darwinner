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

	const string& brand() const;
	uint32 buys() const;
	uint32 cost() const;
	const string& description() const;
	short discount() const;
	uint32 id() const;
	const string& name() const;
	uint32 price() const;
	uint32 sales() const;
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
	const string& specification()  const;
	uint32 stocks()  const;
	uint32 type() const;
	short getAdjustable() const;
	void setAdjustable(short newVal);
	short getRating()  const;
	void setRating(short newVal);
	bool isDualDiscoutn()  const;
	void setDualDiscoutn(bool newVal);
	void clear();

	inline bool operator==(const Business &x){
		return ( m_brand== x.brand() &&
					m_buys== x.buys() &&
					m_cost== x.cost() &&
					m_description== x.description() &&
					m_discount== x.discount() &&
					m_id== x.id() &&
					m_name== x.name() &&
					m_price== x.price() &&
					m_sales== x.sales() &&
					m_specification== x.description() &&
					m_stocks== x.stocks() &&
					m_type== x.type() &&
					m_adjustable== x.getAdjustable() &&
					m_rating== x.getRating() &&
					m_dualDiscoutn== x.isDualDiscoutn()
			);
	}

	class BusinessIdMatcher {
	public:
		BusinessIdMatcher(uint32 id):m_val(id) { }
		inline bool operator()(const Business &x) const
		{
			return 0 == x.id() || x.id() == m_val;
		}
	private:
		uint32 m_val;
	};


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
	short m_adjustable;
	short m_rating;
	bool m_dualDiscoutn;

};
#endif // !defined(EA_F40DCE33_D8D3_43b0_ABAF_0743D8FE2008__INCLUDED_)
