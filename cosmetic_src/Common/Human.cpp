///////////////////////////////////////////////////////////
//  Human.cpp
//  Implementation of the Class Human
//  Created on:      15-May-2009 4:27:36 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Human.h"


Human::Human()
:m_address(""),m_cell(""),m_description(""),m_id(0)
,m_name(""),m_password(""),m_phone(""),m_sex(0)
{

}



Human::~Human(){

}



void Human::clear(){
	m_address= "";
	m_cell= "";
	m_description= "";
	m_id= 0;
	m_name= "";
	m_password= "";
	m_phone= "";
	m_sex= 0;
}


string& Human:: address(){

	return m_address;
}


string& Human:: cell(){

	return m_cell;
}


string& Human:: description(){

	return m_description;
}


uint32& Human:: id(){

	return m_id;
}


string& Human:: name(){

	return m_name;
}


string& Human:: password(){

	return m_password;
}


string& Human:: phone(){

	return m_phone;
}


short& Human:: sex(){

	return m_sex;
}

void Human::setaddress(const string& newVal){

	m_address = newVal;
}


void Human::setcell(const string& newVal){

	m_cell = newVal;
}


void Human::setdescription(const string& newVal){

	m_description = newVal;
}


void Human::setid(const uint32& newVal){

	m_id = newVal;
}


void Human::setname(const string& newVal){

	m_name = newVal;
}


void Human::setpassword(const string& newVal){

	m_password = newVal;
}


void Human::setphone(const string& newVal){

	m_phone = newVal;
}


void Human::setsex(const short& newVal){

	m_sex = newVal;
}

