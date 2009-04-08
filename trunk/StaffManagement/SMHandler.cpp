///////////////////////////////////////////////////////////
//  SMHandler.cpp
//  Implementation of the Class SMHandler
//  Created on:      08-Apr-2009 14:40:22 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "SMHandler.h"
#include "Message.h"
#include "messagedef.h"
#include "IActionHandler.h"
#include "StaffManagementUI.h"
#include "Singleton.cpp"


SMHandler::SMHandler(){
	m_mainWindow = NULL;
}



SMHandler::~SMHandler(){

}


void SMHandler::Start(){

}


void SMHandler::StartAction(Message& act){
	m_handler->StartAction(act);
}

void SMHandler::OnEvent(Message &ev)
{
	switch(ev.type())
	{
		case EVENT_STAFFMGNT:
		{
			if(NULL == m_mainWindow) {
				m_mainWindow = Singleton<StaffManagementUI>::instance();
				m_mainWindow->SetHandler(this);
				SetObserver(m_mainWindow);
			}
			break;
		}
	}
	BroadcastEvent(ev);
}