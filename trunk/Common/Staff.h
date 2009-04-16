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
	byte Sex();
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
	byte status();
	void SetBaseSalary(uint32 salary);
	uint32 baseSalary();
	void clear();

private:
	string m_address;
	string m_cell;
	string m_descrp;
	uint32 m_id;
	uint32 m_level;
	string m_name;
	string m_password;
	string m_phone;
	byte m_sex;
	uint32 m_type;
	byte m_status;
	uint32 m_baseSalary;
};


#endif // !defined(EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_)