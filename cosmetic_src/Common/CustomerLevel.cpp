///////////////////////////////////////////////////////////
//  CustomerLevel.cpp
//  Implementation of the Class CustomerLevel
//  Created on:      24-ÎåÔÂ-2009 17:20:30
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "CustomerLevel.h"


CustomerLevel::CustomerLevel()
:m_description(""),m_discount(100),m_id(0),m_totalCosume(0)
{

}



CustomerLevel::~CustomerLevel(){

}





const string& CustomerLevel::getDescription(){

	return m_description;
}


short CustomerLevel::getDiscount(){

	return m_discount;
}


uint32 CustomerLevel::getId(){

	return m_id;
}


uint64 CustomerLevel::getTotalCosume(){

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