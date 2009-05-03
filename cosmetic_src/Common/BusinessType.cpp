///////////////////////////////////////////////////////////
//  BusinessType.cpp
//  Implementation of the Class BusinessType
//  Created on:      03-ÎåÔÂ-2009 11:26:32
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "BusinessType.h"


BusinessType::BusinessType(){
	m_category = BusinessCost;
	m_description.clear();
	m_id = 0;
	m_name.clear();
}



BusinessType::~BusinessType(){

}





short BusinessType::getCategory(){

	return m_category;
}


string& BusinessType::getDescription(){

	return m_description;
}


uint32 BusinessType::getId(){

	return m_id;
}


string& BusinessType::getName(){

	return m_name;
}


void BusinessType::setCategory(short newVal){

	m_category = newVal;
}


void BusinessType::setDescription(string& newVal){

	m_description = newVal;
}


void BusinessType::setId(uint32 newVal){

	m_id = newVal;
}


void BusinessType::setName(string& newVal){

	m_name = newVal;
}


void BusinessType::setDescription(string newVal){

	m_description = newVal;
}


void BusinessType::setName(string newVal){

	m_name = newVal;
}