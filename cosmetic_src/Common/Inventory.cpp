///////////////////////////////////////////////////////////
//  Inventory.cpp
//  Implementation of the Class Inventory
//  Created on:      03-ÁùÔÂ-2009 12:10:37
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Inventory.h"


Inventory::Inventory(){

}



Inventory::~Inventory(){

}





uint64 Inventory::getActualInventory(){

	return m_actualInventory;
}


uint64 Inventory::getCalculatedInventory(){

	return m_calculatedInventory;
}


string Inventory::getDate(){

	return m_date;
}


uint32 Inventory::getId(){

	return m_id;
}


void Inventory::setActualInventory(uint64 newVal){

	m_actualInventory = newVal;
}


void Inventory::setCalculatedInventory(uint64 newVal){

	m_calculatedInventory = newVal;
}


void Inventory::setDate(string newVal){

	m_date = newVal;
}


void Inventory::setId(uint32 newVal){

	m_id = newVal;
}


uint32 Inventory::getSalesId(){

	return m_salesId;
}


void Inventory::setSalesId(uint32 newVal){

	m_salesId = newVal;
}


int Inventory::getDifference(){

	return 0;
}