///////////////////////////////////////////////////////////
//  IEventObserver.cpp
//  Implementation of the Class IEventObserver
//  Created on:      02-Apr-2009 18:03:01
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "IEventObserver.h"

void IEventObserver::SetHandler(IActionHandler* handler){
	m_handler = handler;
}

IActionHandler* IEventObserver::GetHandler(){
	return m_handler;
}
