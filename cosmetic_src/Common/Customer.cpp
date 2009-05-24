///////////////////////////////////////////////////////////
//  Customer.cpp
//  Implementation of the Class Customer
//  Created on:      24-ÎåÔÂ-2009 17:15:39
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Customer.h"


Customer::Customer()
:m_consumeTime(0),m_deposit(0),m_level(0)
{

}



Customer::~Customer(){

}





uint32 Customer:: consumeTime(){

	return m_consumeTime;
}


uint32 Customer:: deposit(){

	return m_deposit;
}


uint32 Customer:: level(){

	return m_level;
}


void Customer::setconsumeTime(uint32 newVal){

	m_consumeTime = newVal;
}


void Customer::setdeposit(uint32 newVal){

	m_deposit = newVal;
}


void Customer::setlevel(uint32 newVal){

	m_level = newVal;
}