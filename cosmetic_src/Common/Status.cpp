///////////////////////////////////////////////////////////
//  Status.cpp
//  Implementation of the Class Status
//  Created on:      17-ËÄÔÂ-2009 14:02:03
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "Status.h"


Status::Status(){
	m_description.clear();
	m_id = 0;
	m_name.clear();
}

Status::~Status(){

}

string Status::description(){

	return  m_description;
}


uint32 Status::id(){

	return  m_id;
}


string Status::name(){

	return  m_name;
}

void Status::setDescription(string descr){
	m_description = descr;
}


void Status::setId(uint32 id){
	m_id = id;
}

void Status::setName(string name){
	m_name = name;
}
