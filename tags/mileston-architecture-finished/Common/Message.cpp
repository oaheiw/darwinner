///////////////////////////////////////////////////////////
//  Message.cpp
//  Implementation of the Class Message
//  Created on:      02-ËÄÔÂ-2009 18:03:38
//  Original author: Sunlight Kuo
///////////////////////////////////////////////////////////

#include "Message.h"


Message::Message(){
	m_data = NULL;
	m_length = 0;
	m_type = 0;
}

Message::Message(void* data){
	m_data = data;
	m_length = 0;
	m_type = 0;
}

Message::Message(uint32 type, void* data){
	m_data = data;
	m_length = 0;
	m_type = type;
}

Message::~Message(){

}


uint32 Message::length(){

	return  m_length;
}


void Message::setData(void* data, uint32 size){
	memcpy(m_data, data, size);
}

void Message::setData(void* data){
	m_data = data;
}

void* Message::data(){
	return m_data;
}

void Message::setLength(uint32 length){
	m_length = length;
}


void Message::setType(uint32 type){
	m_type = type;
}


uint32 Message::type(){

	return  m_type;
}
/*
Message::Message(const Message &rs)  
  {  
	if(this != &rs)  
	{ 
		memcpy(m_data, rs.m_data, MESSAGE_BUFFER_SIZE);
		m_length = rs.m_length;
		m_type = rs.m_type;
		m_id = rs.m_id;
	} 
  }  
   
  Message   &Message::operator=(const   Message   &   rs)  
  {  
	if(this != &rs)  
	{ 
		memcpy(m_data, rs.m_data, MESSAGE_BUFFER_SIZE);
		m_length = rs.m_length;
		m_type = rs.m_type;
		m_id = rs.m_id;
	} 
  return *this;  
  }   
  */