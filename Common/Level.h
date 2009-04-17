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

private:
	string m_description;
	uint32 m_id;
	string m_name;
	short m_profit;

};
#endif // !defined(EA_E7DB82B0_1E35_4081_8BAA_B3494CB31864__INCLUDED_)
