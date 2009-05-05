///////////////////////////////////////////////////////////
//  Business.cpp
//  Implementation of the Class Business
//  Created on:      02-ÎåÔÂ-2009 22:33:26
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Business.h"


Business::Business(){
	m_brand.clear();
	m_buys = 0;
	m_cost = 0;
	m_description.clear();
	m_discount = 100;
	m_id = 0;
	m_name.clear();
	m_price = 0;
	m_sales = 0;
	m_specification.clear();
	m_stocks = 0;
	m_type = 0;
	m_rating = 60;
}



Business::~Business(){

}





string& Business::brand(){

	return  m_brand;
}


uint32 Business::buys(){

	return  m_buys;
}


uint32 Business::cost(){

	return  m_cost;
}


string& Business::description(){

	return  m_description;
}


short Business::discount(){

	return m_discount;
}


uint32 Business::id(){

	return  m_id;
}


string& Business::name(){

	return  m_name;
}


uint32 Business::price(){

	return  m_price;
}


uint32 Business::sales(){

	return  m_sales;
}


void Business::setBrand(string brand){
	m_brand = brand;
}


void Business::setBuys(uint32 buys){
	m_buys = buys;
}


void Business::setCost(uint32 cost){
	m_cost = cost;
}


void Business::setDescription(string description){
	m_description = description;
}


void Business::setDiscount(short discount){
	m_discount = discount;
}


void Business::setId(uint32 id){
	m_id = id;
}


void Business::setName(string name){
	m_name = name;
}


void Business::setPrice(uint32 price){
	m_price = price;
}


void Business::setSales(uint32 sales){
	m_sales = sales;
}


void Business::setSpecification(string specification){
	m_specification = specification;
}


void Business::setStocks(uint32 stocks){
	m_stocks =  stocks;
}


void Business::setType(uint32 type){
	m_type = type;
}


string& Business::specification(){

	return  m_specification;
}


uint32 Business::stocks(){

	return  m_stocks;
}


uint32 Business::type(){

	return  m_type;
}



short Business::getAdjustable(){

	return m_adjustable;
}


void Business::setAdjustable(short newVal){

	m_adjustable = newVal;
}

short Business::getRating(){

	return m_rating;
}


void Business::setRating(short newVal){

	m_rating = newVal;
}


bool Business::isDualDiscoutn(){

	return m_dualDiscoutn;
}


void Business::setDualDiscoutn(bool newVal){

	m_dualDiscoutn = newVal;
}