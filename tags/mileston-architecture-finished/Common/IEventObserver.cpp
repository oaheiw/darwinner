///////////////////////////////////////////////////////////
//  IEventObserver.cpp
//  Implementation of the Class IEventObserver
//  Created on:      02-ËÄÔÂ-2009 18:03:01
//  Original author: Sunlight Kuo
///////////////////////////////////////////////////////////

#include "IEventObserver.h"

void IEventObserver::SetHandler(IActionHandler* handler){
	m_handler = handler;
}
