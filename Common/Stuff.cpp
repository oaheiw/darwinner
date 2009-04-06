///////////////////////////////////////////////////////////
//  Stuff.cpp
//  Implementation of the Class Stuff
//  Created on:      03-ËÄÔÂ-2009 18:24:52
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Stuff.h"


Stuff::Stuff(){

}



Stuff::~Stuff(){

}





string Stuff::Descrp(){

	return  m_descrp;
}


string Stuff::ID(){

	return  m_id;
}


uint32 Stuff::Level(){

	return  m_level;
}


string Stuff::Name(){

	return  m_name;
}


string Stuff::Password(){

	return  m_password;
}


void Stuff::SetDescrp(string descrp){
	m_descrp = descrp;

}


void Stuff::SetID(string id){
	m_id = id;
}


void Stuff::SetLevel(uint32 level){
	m_level = level;

}


void Stuff::SetName(string name){
	m_name = name;
}


void Stuff::SetPassword(string pw){
	m_password = pw;
}


void Stuff::SetType(uint32 type){
	m_type = type;
}


uint32 Stuff::Type(){

	return  m_type;
}

void Stuff::SetSex(byte sex){
	m_sex = sex;
}


byte Stuff::Sex(){

	return  m_sex;
}