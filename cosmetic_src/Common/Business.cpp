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
	m_adjustable = 0;
	m_dualDiscoutn = false;
}



Business::~Business(){

}

void Business::clear(){
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
	m_adjustable = 0;
	m_dualDiscoutn = false;
}



const string& Business::brand() const {

	return  m_brand;
}


uint32 Business::buys() const{

	return  m_buys;
}


uint32 Business::cost() const{

	return  m_cost;
}


const string& Business::description() const{

	return  m_description;
}


short Business::discount() const{

	return m_discount;
}


uint32 Business::id() const{

	return  m_id;
}


const string& Business::name() const{

	return  m_name;
}


uint32 Business::price() const{

	return  m_price;
}


uint32 Business::sales() const{

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


const string& Business::specification() const{

	return  m_specification;
}


uint32 Business::stocks() const{

	return  m_stocks;
}


uint32 Business::type() const{

	return  m_type;
}



short Business::getAdjustable() const{

	return m_adjustable;
}


void Business::setAdjustable(short newVal){

	m_adjustable = newVal;
}

short Business::getRating() const{

	return m_rating;
}


void Business::setRating(short newVal){

	m_rating = newVal;
}


bool Business::isDualDiscoutn() const{

	return m_dualDiscoutn;
}


void Business::setDualDiscoutn(bool newVal){

	m_dualDiscoutn = newVal;
}