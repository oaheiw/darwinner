///////////////////////////////////////////////////////////
//  IActionHandler.cpp
//  Implementation of the Class IActionHandler
//  Created on:      02-Apr-2009 18:09:50
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "IActionHandler.h"
#include "IEventObserver.h"

void IActionHandler::SetObserver(IEventObserver* observer){
	list<IEventObserver*>::iterator it = m_listObserver.begin();

	while(m_listObserver.end() != it) {
		if(*it == observer) return;
		it++;
	}
	m_listObserver.push_back(observer);
	int size = m_listObserver.size();
}

void IActionHandler::BroadcastEvent(Message& ev){
	list<IEventObserver*>::const_iterator it = m_listObserver.begin();
	int size = m_listObserver.size();
	while(m_listObserver.end() != it) {
		if(NULL != *it) {
			(*it)->OnEvent(ev);
		}
		it++;
	}
}

void IActionHandler::DeregisterObserver(IEventObserver* observer){
//	list<IEventObserver*>::iterator it = m_listObserver.begin();
//	while(m_listObserver.end() != it) {
//		if(*it == observer) {
			m_listObserver.remove(observer);
//		}
//		it++;
//	}
}