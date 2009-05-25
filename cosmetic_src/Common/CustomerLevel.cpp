///////////////////////////////////////////////////////////
//  CustomerLevel.cpp
//  Implementation of the Class CustomerLevel
//  Created on:      24-ÎåÔÂ-2009 17:20:30
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "CustomerLevel.h"


CustomerLevel::CustomerLevel()
:m_description(""),m_discount(100),m_id(0),m_totalCosume(0),m_name("")
{

}



CustomerLevel::~CustomerLevel(){

}


const string& CustomerLevel::getDescription() const{

	return m_description;
}


const short CustomerLevel::getDiscount() const{

	return m_discount;
}


const uint32 CustomerLevel::getId() const{

	return m_id;
}


const uint64 CustomerLevel::getTotalCosume() const{

	return m_totalCosume;
}


void CustomerLevel::setDescription(const string& newVal){

	m_description = newVal;
}


void CustomerLevel::setDiscount(short newVal){

	m_discount = newVal;
}


void CustomerLevel::setId(uint32 newVal){

	m_id = newVal;
}


void CustomerLevel::setTotalCosume(uint64 newVal){

	m_totalCosume = newVal;
}


const string& CustomerLevel::getName() const{

	return m_name;
}


void CustomerLevel::setName(const string& newVal){

	m_name = newVal;
}