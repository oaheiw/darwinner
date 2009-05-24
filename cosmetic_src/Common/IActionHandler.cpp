///////////////////////////////////////////////////////////
//  IActionHandler.cpp
//  Implementation of the Class IActionHandler
//  Created on:      02-Apr-2009 18:09:50
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "IActionHandler.h"
#include "IEventObserver.h"
#include "Message.h"

void IActionHandler::SetObserver(IEventObserver* observer){
	list<IEventObserver*>::iterator it = m_listObserver.begin();

	while(m_listObserver.end() != it) {
		if(*it == observer) return;
		it++;
	}
	
	m_listObserver.push_back(observer);
	DBHEX("one observer inserted:", observer);
}

void IActionHandler::BroadcastEvent(Message& ev){
	DBHEX("broadcasted message :", ev.type());
	list<IEventObserver*>::const_iterator it = m_listObserver.begin();
	while(m_listObserver.end() != it) {
		if(NULL != *it) {
			(*it)->OnEvent(ev);
		}
		it++;
	}
}

void IActionHandler::DeregisterObserver(IEventObserver* observer){
	m_listObserver.remove(observer);
}


bool IActionHandler::checkRight(uint32 actionId){
	return true;
}