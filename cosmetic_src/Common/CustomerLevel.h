///////////////////////////////////////////////////////////
//  CustomerLevel.h
//  Implementation of the Class CustomerLevel
//  Created on:      24-ÎåÔÂ-2009 17:20:30
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_4095633F_D068_4352_B8DA_B6BC33B23102__INCLUDED_)
#define EA_4095633F_D068_4352_B8DA_B6BC33B23102__INCLUDED_

#include "common.h"
#include <string>
using namespace std;

class CustomerLevel
{

public:
	CustomerLevel();
	virtual ~CustomerLevel();

	const string& getDescription() const;
	const short getDiscount() const;
	const uint32 getId() const;
	const uint64 getTotalCosume() const;
	void setDescription(const string& newVal);
	void setDiscount(short newVal);
	void setId(uint32 newVal);
	void setTotalCosume(uint64 newVal);
	const string& getName() const;
	void setName(const string& newVal);

	friend inline bool operator==(const CustomerLevel &x, const CustomerLevel &y){
		return ( y.m_id == x.m_id &&
			y.m_name == x.m_name &&
			y.m_discount == x.m_discount &&
			y.m_totalCosume == x.m_totalCosume &&
			y.m_description == x.m_description
			);
	}


	class CustomerLevelIdMatcher {
	public:
		CustomerLevelIdMatcher(uint32 id):m_val(id) { }
		inline bool operator()(const CustomerLevel &x) const
		{
			return x.getId() == m_val;
		}
	private:
		uint32 m_val;
	};

private:
	string m_description;
	short m_discount;
	uint32 m_id;
	uint64 m_totalCosume;
	string m_name;

};
#endif // !defined(EA_4095633F_D068_4352_B8DA_B6BC33B23102__INCLUDED_)
