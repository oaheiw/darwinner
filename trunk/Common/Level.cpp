///////////////////////////////////////////////////////////
//  Level.cpp
//  Implementation of the Class Level
//  Created on:      17-ËÄÔÂ-2009 14:08:55
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Level.h"


Level::Level(){
	m_description.clear();
	m_id = 0;
	m_name.clear();
	m_profit = 0;
}



Level::~Level(){

}





string Level::description(){

	return  m_description;
}


uint32 Level::id(){

	return  m_id;
}


string Level::name(){

	return  m_name;
}


short Level::profit(){

	return m_profit;
}


void Level::setDescription(string descr){
	m_description = descr;
}


void Level::setId(uint32 id){
	m_id = id;
}


void Level::setName(string name){
	m_name = name;
}


void Level::setProfit(uint32 profit){
	m_profit = profit;
}