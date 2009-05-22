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
	~BusinessType();
	short getCategory() const;
	const string& getDescription() const;
	uint32 getId() const;
	const string& getName() const;
	void setCategory(short newVal);
	void setDescription(const string& newVal);
	void setId(uint32 newVal);
	void setName(const string& newVal);

	friend inline bool operator==(const BusinessType &x, const BusinessType &y){
		return ( y.m_category == x.m_category &&
				y.m_description == x.m_description &&
				y.m_id == x.m_id &&
				y.m_name == x.m_name
			);
	}
/*
	friend class BusinessTypeFullMatcher {
	public:
		BusinessTypeFullMatcher(const BusinessType& businesstype):m_val(businesstype) { }
		inline bool operator()(const BusinessType &x)
		{
			return m_val == x;
		}
	private:
		const BusinessType m_val;
	};
*/
	class BusinessTypeIdMatcher {
	public:
		BusinessTypeIdMatcher(uint32 id):m_val(id) { }
		inline bool operator()(const BusinessType &x) const
		{
			return x.getId() == m_val;
		}
	private:
		uint32 m_val;
	};

private:
	short m_category;
	string m_description;
	uint32 m_id;
	string m_name;

};
#endif // !defined(EA_193F396C_5504_41cb_9F33_67D4F69EA264__INCLUDED_)
