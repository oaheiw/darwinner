///////////////////////////////////////////////////////////
//  CustomerLevel.h
//  Implementation of the Class CustomerLevel
//  Created on:      24-ÎåÔÂ-2009 17:20:30
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_4095633F_D068_4352_B8DA_B6BC33B23102__INCLUDED_)
#define EA_4095633F_D068_4352_B8DA_B6BC33B23102__INCLUDED_

#include "common.h"

class CustomerLevel
{

public:
	CustomerLevel();
	virtual ~CustomerLevel();

	const string& getDescription();
	short getDiscount();
	uint32 getId();
	uint64 getTotalCosume();
	void setDescription(const string& newVal);
	void setDiscount(short newVal);
	void setId(uint32 newVal);
	void setTotalCosume(uint64 newVal);

private:
	string m_description;
	short m_discount;
	uint32 m_id;
	uint64 m_totalCosume;

};
#endif // !defined(EA_4095633F_D068_4352_B8DA_B6BC33B23102__INCLUDED_)
