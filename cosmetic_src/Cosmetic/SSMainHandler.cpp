///////////////////////////////////////////////////////////
//  MainDispatcher.cpp
//  Implementation of the Class MainDispatcher
//  Created on:      02-Apr-2009 18:03:22
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "SSMainHandler.h"
#include "SSLoginWindow.h"
#include "SSMainMenu.h"
#include "Message.h"
#include "messagedef.h"
#include "IActionHandler.h"
#include "Singleton.h"
#include "Guide.h"

SSMainHandler::SSMainHandler()
{
	m_entryWindow = NULL;
	m_mainWindow = NULL;
	m_Wizard = NULL;
}



SSMainHandler::~SSMainHandler(){

}

void SSMainHandler::StartAction(Message & act)
{
	switch(act.type()) {

	}
	m_handler->StartAction(act);
}

void SSMainHandler::OnEvent(Message& Msg)
{
	switch(Msg.type()) {
		case EVENT_SYSTEM_START: 
		{
			if(NULL == m_entryWindow) {
				m_entryWindow = Singleton<SSLoginWindow>::instance();
				m_entryWindow->SetHandler(this);
				SetObserver(m_entryWindow);
			}
			if(NULL == m_mainWindow) {
				m_mainWindow =  Singleton<SSMainMenu>::instance();
				m_mainWindow->SetHandler(this);
				SetObserver(m_mainWindow);
			}
			break;
		}
		case EVENT_WIZARD: 
		{
			if(NULL == m_Wizard) {
				m_Wizard =  Singleton<Guide>::instance();
				m_Wizard->SetHandler(this);
				SetObserver(m_Wizard);
			}
			break;
		}
	}

	BroadcastEvent(Msg);
}

