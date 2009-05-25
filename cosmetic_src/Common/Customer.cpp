///////////////////////////////////////////////////////////
//  Customer.cpp
//  Implementation of the Class Customer
//  Created on:      24-ÎåÔÂ-2009 17:15:39
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "Customer.h"

Customer::Customer(){

}



Customer::~Customer(){

}





uint32 Customer::getConsumeTime(){

	return m_consumeTime;
}


uint64 Customer::getDeposit(){

	return m_deposit;
}


uint32 Customer::getLevel(){

	return m_level;
}


uint64 Customer::getTotalConsume(){

	return m_totalConsume;
}


void Customer::setConsumeTime(uint32 newVal){

	m_consumeTime = newVal;
}


void Customer::setDeposit(uint64 newVal){

	m_deposit = newVal;
}


void Customer::setLevel(uint32 newVal){

	m_level = newVal;
}


void Customer::setTotalConsume(uint64 newVal){

	m_totalConsume = newVal;
}