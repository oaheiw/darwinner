///////////////////////////////////////////////////////////
//  BusinessType.cpp
//  Implementation of the Class BusinessType
//  Created on:      03-ÎåÔÂ-2009 11:26:32
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "BusinessType.h"


BusinessType::BusinessType(){
	m_category = 0;
	m_description.clear();
	m_id = 0;
	m_name.clear();
}



BusinessType::~BusinessType(){

}





short BusinessType::getCategory() const{

	return m_category;
}


const string& BusinessType::getDescription() const{

	return m_description;
}


uint32 BusinessType::getId() const{

	return m_id;
}


const string& BusinessType::getName() const{

	return m_name;
}


void BusinessType::setCategory(short newVal){

	m_category = newVal;
}


void BusinessType::setDescription(const string& newVal){

	m_description = newVal;
}


void BusinessType::setId(uint32 newVal){

	m_id = newVal;
}


void BusinessType::setName(const string& newVal){

	m_name = newVal;
}
