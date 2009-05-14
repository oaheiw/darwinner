///////////////////////////////////////////////////////////
//  DUIObserver.cpp
//  Implementation of the Class DUIObserver
//  Created on:      07-Apr-2009 5:06:44 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "DUIObserver.h"
#include "common.h"

DUIObserver::DUIObserver(){
	m_uiHandler = NULL;
}



DUIObserver::~DUIObserver(){

}

void DUIObserver::SetHandler(DUIHandler* handler){
	m_uiHandler = handler;
}


DUIHandler* DUIObserver::GetHandler(){

	return  m_uiHandler;
}
