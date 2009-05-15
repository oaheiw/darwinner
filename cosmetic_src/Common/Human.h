///////////////////////////////////////////////////////////
//  Human.h
//  Implementation of the Class Human
//  Created on:      15-May-2009 4:27:36 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_3069FA9E_346B_4c7a_9D73_B4831372F2EB__INCLUDED_)
#define EA_3069FA9E_346B_4c7a_9D73_B4831372F2EB__INCLUDED_

#include "common.h"

class Human
{

public:
	Human();
	virtual ~Human();
	string&  address();
	string&  cell();
	string&  description();
	uint32&  id();
	string&  name();
	string&  password();
	string&  phone();
	short&  sex();
	virtual void clear();
	void setaddress(const string& newVal);
	void setcell(const string& newVal);
	void setdescription(const string& newVal);
	void setid(const uint32& newVal);
	void setname(const string& newVal);
	void setpassword(const string& newVal);
	void setphone(const string& newVal);
	void setsex(const short& newVal);

	friend inline bool operator==(const Human& x, const Human& y){
			return (	y.m_description== x.m_description&&
						y.m_id == x.m_id &&
						y.m_name == x.m_name &&
						y.m_password ==x.m_password &&
						y.m_sex == x.m_sex &&
						y.m_address == x.m_address &&
						y.m_cell == x.m_cell &&
						y.m_phone == x.m_phone);

	}

private:
	string m_address;
	string m_cell;
	string m_description;
	uint32 m_id;
	string m_name;
	string m_password;
	string m_phone;
	short m_sex;

};
#endif // !defined(EA_3069FA9E_346B_4c7a_9D73_B4831372F2EB__INCLUDED_)
