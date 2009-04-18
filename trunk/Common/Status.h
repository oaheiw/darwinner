///////////////////////////////////////////////////////////
//  Status.h
//  Implementation of the Class Status
//  Created on:      17-ËÄÔÂ-2009 14:02:03
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_7666D1A4_1FAF_4bed_81C2_8CFACB8695FE__INCLUDED_)
#define EA_7666D1A4_1FAF_4bed_81C2_8CFACB8695FE__INCLUDED_
#include "common.h"
#include <string>
using namespace std;
class Status
{

public:
	Status();
	virtual ~Status();

	string description();
	uint32 id();
	string name();
	void setDescription(string descr);
	void setId(uint32 id);
	void setName(string name);

private:
	string m_description;
	uint32 m_id;
	string m_name;
};
#endif // !defined(EA_7666D1A4_1FAF_4bc7_81C2_8CFACB8695FE__INCLUDED_)
