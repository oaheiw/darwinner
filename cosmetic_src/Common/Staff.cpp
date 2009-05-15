///////////////////////////////////////////////////////////
//  Staff.cpp
//  Implementation of the Class Staff
//  Created on:      03-Apr-2009 18:24:52
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Staff.h"


Staff::Staff()
:m_bonus(0),m_level(0),m_rating(50),m_status(0),m_type(0){
	Human::clear();
}

Staff::~Staff(){

}


void Staff::clear(){
	Human::clear();
	m_level = 0;
	m_status = 0;
	m_bonus = 0;
	m_rating= 0;
	m_type = 0;
}

void Staff::setbonus(const uint32& newVal){

	m_bonus = newVal;
}


void Staff::setlevel(const uint32& newVal){

	m_level = newVal;
}


void Staff::setrating(const short& newVal){

	m_rating = newVal;
}


void Staff::setstatus(const uint32& newVal){

	m_status = newVal;
}


void Staff::settype(const uint32& newVal){

	m_type = newVal;
}

const uint32& Staff:: bonus() const{

	return m_bonus;
}


const uint32& Staff:: level() const{

	return m_level;
}


const short& Staff:: rating() const{

	return m_rating;
}


const uint32& Staff:: status() const{

	return m_status;
}


const uint32& Staff:: type() const{

	return m_type;
}
