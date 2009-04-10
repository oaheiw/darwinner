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

class DLL_EXPORT Staff
{

public:
	Staff();
	virtual ~Staff();

	string Descrp();
	string  ID();
	uint32 Level();
	string Name();
	string Password();
	void SetDescrp(string descrp);
	void SetID(string id);
	void SetLevel(uint32 level);
	void SetName(string name);
	void SetPassword(string pw);
	void SetType(uint32 type);
	uint32 Type();
	void SetSex(byte sex);
	byte Sex();

private:
	string m_descrp;
	string m_id;
	uint32 m_level;
	string m_name;
	string m_password;
	uint32 m_type;
	byte m_sex;
};
#endif // !defined(EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_)
