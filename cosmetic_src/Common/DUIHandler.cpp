///////////////////////////////////////////////////////////
//  DUIHandler.cpp
//  Implementation of the Class DUIHandler
//  Created on:      07-Apr-2009 5:06:43 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "DUIHandler.h"
#include "DUIObserver.h"

DUIHandler::DUIHandler(){
	m_listUiObserver.clear();
}



DUIHandler::~DUIHandler(){

}

void DUIHandler::SetObserver(DUIObserver* observer){
	list<DUIObserver*>::iterator it = m_listUiObserver.begin();

	while(m_listUiObserver.end() != it) {
		if(*it == observer) return;
		it++;
	}
	m_listUiObserver.push_back(observer);
}

void DUIHandler::BroadcastEvent(Message& ev){
	list<DUIObserver*>::const_iterator it = m_listUiObserver.begin();
	while(m_listUiObserver.end() != it) {
		if(NULL != *it) {
			(*it)->OnEvent(ev);
		}
		it++;
	}
}

void DUIHandler::DeregisterObserver(DUIObserver* observer){
	m_listUiObserver.remove(observer);
}

bool DUIHandler::CheckRight(uint32 actionId){
	return true;
}