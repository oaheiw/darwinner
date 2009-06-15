///////////////////////////////////////////////////////////
//  Stock.cpp
//  Implementation of the Class Stock
//  Created on:      03-ÁùÔÂ-2009 12:10:40
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Stock.h"


Stock::Stock(){

}



Stock::~Stock(){

}





uint64 Stock::getAmount(){

	return m_amount;
}


short Stock::getDirction(){

	return m_dirction;
}


uint64 Stock::getId(){

	return m_id;
}


uint32 Stock::getSalesId(){

	return m_salesId;
}


string Stock::getStockingDate(){

	return m_stockingDate;
}


double32 Stock::getUnitPrice(){

	return m_unitPrice;
}


void Stock::setAmount(uint64 newVal){

	m_amount = newVal;
}


void Stock::setDirction(short newVal){

	m_dirction = newVal;
}


void Stock::setId(uint64 newVal){

	m_id = newVal;
}


void Stock::setSalesId(uint32 newVal){

	m_salesId = newVal;
}


void Stock::setStockingDate(string newVal){

	m_stockingDate = newVal;
}


void Stock::setUnitPrice(double32 newVal){

	m_unitPrice = newVal;
}


string& Stock::getDate(){

	return m_date;
}


void Stock::setDate(string& newVal){

	m_date = newVal;
}
