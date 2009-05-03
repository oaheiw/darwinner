///////////////////////////////////////////////////////////
//  Staff.cpp
//  Implementation of the Class Staff
//  Created on:      03-Apr-2009 18:24:52
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Staff.h"


Staff::Staff(){
	m_descrp.clear();
	m_id= 0;
	m_level = 0;
	m_name.clear();
	m_password.clear();
	m_type = 0;
	m_sex = 0;
	m_address.clear();
	m_cell.clear();
	m_phone.clear();
	m_status = 0;
	m_baseSalary = 0;
	m_rating = 60;
}

Staff::~Staff(){

}


void Staff::clear(){
	m_descrp.clear();
	m_id= 0;
	m_level = 0;
	m_name.clear();
	m_password.clear();
	m_type = 0;
	m_sex = 0;
	m_address.clear();
	m_cell.clear();
	m_phone.clear();
	m_status = 0;
	m_rating = 0;
}

string Staff::Descrp(){

	return  m_descrp;
}


uint32 Staff::Level(){

	return  m_level;
}


string Staff::Name(){

	return  m_name;
}


string Staff::Password(){
	return  m_password;
}


void Staff::SetDescrp(string descrp){
	m_descrp = descrp;
}

void Staff::SetID(uint32 id){
	m_id = id;
}


void Staff::SetLevel(uint32 level){
	m_level = level;

}


void Staff::SetName(string name){
	m_name = name;
}


void Staff::SetPassword(string pw){
	m_password = pw;
}


void Staff::SetType(uint32 type){
	m_type = type;
}

uint32 Staff::ID(){
	return m_id;
}

uint32 Staff::Type(){

	return  m_type;
}

void Staff::SetSex(byte sex){
	m_sex = sex;
}


uint32 Staff::Sex(){

	return  m_sex;
}

string Staff::address(){

	return  m_address;
}


string Staff::cell(){

	return  m_cell;
}


string Staff::phone(){

	return  m_phone;
}


void Staff::SetAddress(string address){
		m_address = address;
}


void Staff::SetCell(string cell){
	m_cell = cell;
}

void Staff::SetPhone(string phone){
		m_phone = phone;
}

void Staff::SetStatus(byte status){
		m_status = status;
}
uint32 Staff::status(){

	return  m_status;
}
void Staff::SetBaseSalary(uint32 salary){
		m_baseSalary = salary;
}
uint32 Staff::baseSalary(){

	return  m_baseSalary;
}




short Staff::getRating(){

	return m_rating;
}


void Staff::setRating(short newVal){

	m_rating = newVal;
}