///////////////////////////////////////////////////////////
//  DUIHandler.cpp
//  Implementation of the Class DUIHandler
//  Created on:      07-Apr-2009 5:06:43 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "DUIHandler.h"


DUIHandler::DUIHandler(){
	m_uiObserver = NULL;
}



DUIHandler::~DUIHandler(){

}

void DUIHandler::SetObserver(DUIObserver* observer){
	m_uiObserver = observer;
}

DUIObserver* DUIHandler::GetObserver(){

	return  m_uiObserver;
}