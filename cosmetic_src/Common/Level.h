///////////////////////////////////////////////////////////
//  Level.h
//  Implementation of the Class Level
//  Created on:      17-ËÄÔÂ-2009 14:08:55
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_E7DB82B0_1E35_4081_8BAA_B3494CB31864__INCLUDED_)
#define EA_E7DB82B0_1E35_4081_8BAA_B3494CB31864__INCLUDED_
#include "common.h"
#include <string>
using namespace std;

class Level
{

public:
	Level();
	virtual ~Level();

	string description();
	uint32 id();
	string name();
	short profit();
	void setDescription(string descr);
	void setId(uint32 id);
	void setName(string name);
	void setProfit(uint32 profit);

friend bool operator==(const Level &x, const Level &y) {
	return (	y.m_description == x.m_description &&
				y.m_id == x.m_id &&
				y.m_name == x.m_name &&
				y.m_profit == x.m_profit);
}

class idMatcher {
public:
	idMatcher(uint32 id) { m_val = id; }
	bool operator()(Level& x) 
	{
		return x.id() == m_val;
	}
private:
	uint32 m_val;
};


private:
	string m_description;
	uint32 m_id;
	string m_name;
	short m_profit;

};
#endif // !defined(EA_E7DB82B0_1E35_4081_8BAA_B3494CB31864__INCLUDED_)
