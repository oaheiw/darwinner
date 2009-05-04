///////////////////////////////////////////////////////////
//  BusinessType.h
//  Implementation of the Class BusinessType
//  Created on:      03-ÎåÔÂ-2009 11:26:31
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_193F396C_5504_41cb_9F33_67D4F69EA264__INCLUDED_)
#define EA_193F396C_5504_41cb_9F33_67D4F69EA264__INCLUDED_

#include "common.h"
#include <string>
using namespace std;

class BusinessType
{
public:
	BusinessType();
	virtual ~BusinessType();

	short getCategory();
	string& getDescription();
	uint32 getId();
	string& getName();
	void setCategory(short newVal);
	void setDescription(string& newVal);
	void setId(uint32 newVal);
	void setName(string& newVal);
	void setDescription(string newVal);
	void setName(string newVal);

private:
	short m_category;
	string m_description;
	uint32 m_id;
	string m_name;

};
#endif // !defined(EA_193F396C_5504_41cb_9F33_67D4F69EA264__INCLUDED_)
