///////////////////////////////////////////////////////////
//  Staff.h
//  Implementation of the Class Staff
//  Created on:      03-Apr-2009 18:24:52
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_)
#define EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_

#include "common.h"
#include <string>
using namespace std;

class Staff
{

public:
	Staff();
	~Staff();
	string address();
	string cell();
	string Descrp();
	uint32 ID();
	uint32 Level();
	string Name();
	string Password();
	string phone();
	uint32 Sex();
	uint32 Type();
	void SetAddress(string descrp);
	void SetCell(string cell);
	void SetDescrp(string descrp);
	void SetID(uint32 id);
	void SetLevel(uint32 level);
	void SetName(string name);
	void SetPassword(string pw);
	void SetPhone(string phone);
	void SetSex(byte sex);
	void SetType(uint32 type);
	void SetStatus(byte status);
	uint32 status();
	void SetBaseSalary(uint32 salary);
	uint32 baseSalary();
	void clear();

	friend bool operator==(const Staff &x, const Staff &y) {
		return (	y.m_descrp == x.m_descrp &&
					y.m_id == x.m_id &&
					y.m_level == x.m_level &&
					y.m_name == x.m_name &&
					y.m_password ==x.m_password &&
					y.m_type == x.m_type &&
					y.m_sex == x.m_sex &&
					y.m_address == x.m_address &&
					y.m_cell == x.m_cell &&
					y.m_phone == x.m_phone &&
					y.m_status == x.m_status &&
					y.m_baseSalary == x.m_baseSalary);
	}

	class idMatcher {
	public:
		idMatcher(uint32 id) { m_val = id; }
		bool operator()(Staff& x) 
		{
			return 0 == x.ID() || x.ID() == m_val;
		}
	private:
		uint32 m_val;
	};

private:
	string m_address;
	string m_cell;
	string m_descrp;
	uint32 m_id;
	uint32 m_level;
	string m_name;
	string m_password;
	string m_phone;
	uint32 m_sex;
	uint32 m_type;
	uint32 m_status;
	uint32 m_baseSalary;
};


#endif // !defined(EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_)