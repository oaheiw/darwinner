///////////////////////////////////////////////////////////
//  Job.h
//  Implementation of the Class Job
//  Created on:      17-ËÄÔÂ-2009 14:02:03
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_7666D1A4_1FAF_4bc7_81C2_8CFACB8695FE__INCLUDED_)
#define EA_7666D1A4_1FAF_4bc7_81C2_8CFACB8695FE__INCLUDED_
#include "common.h"
#include <string>
using namespace std;
class Job
{

public:
	Job();
	virtual ~Job();

	string description();
	uint32 id();
	string name();
	short profit();
	uint32 baseSalary();
	void setDescription(string descr);
	void setId(uint32 id);
	void setName(string name);
	void setProfit(short profit);
	void setBaseSalary(uint32 salary);

	friend bool operator==(const Job &x, const Job &y)
	{
		return (y.m_description == x.m_description && 
			y.m_id == x.m_id && 
			y.m_name == x.m_name &&
			y.m_baseSalary == y.m_baseSalary &&
			y.m_profit == x.m_profit);
	}

	class idMatcher {
	public:
		idMatcher(uint32 id) { m_val = id; }
		bool operator()(Job& x) 
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
	uint32 m_baseSalary;
};
#endif // !defined(EA_7666D1A4_1FAF_4bc7_81C2_8CFACB8695FE__INCLUDED_)
