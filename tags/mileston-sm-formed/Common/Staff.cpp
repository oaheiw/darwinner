///////////////////////////////////////////////////////////
//  Staff.cpp
//  Implementation of the Class Staff
//  Created on:      03-Apr-2009 18:24:52
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Staff.h"


Staff::Staff(){

}



Staff::~Staff(){

}





string Staff::Descrp(){

	return  m_descrp;
}


string Staff::ID(){

	return  m_id;
}


uint32 Staff::Level(){

	return  m_level;
}


string Staff::Name(){

	return  m_name;
}


string Staff::Password(){

	return  m_password;
}


void Staff::SetDescrp(string descrp){
	m_descrp = descrp;

}


void Staff::SetID(string id){
	m_id = id;
}


void Staff::SetLevel(uint32 level){
	m_level = level;

}


void Staff::SetName(string name){
	m_name = name;
}


void Staff::SetPassword(string pw){
	m_password = pw;
}


void Staff::SetType(uint32 type){
	m_type = type;
}


uint32 Staff::Type(){

	return  m_type;
}

void Staff::SetSex(byte sex){
	m_sex = sex;
}


byte Staff::Sex(){

	return  m_sex;
}