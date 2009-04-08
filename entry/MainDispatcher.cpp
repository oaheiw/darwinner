///////////////////////////////////////////////////////////
//  MainDispatcher.cpp
//  Implementation of the Class MainDispatcher
//  Created on:      02-Apr-2009 18:03:22
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "MainDispatcher.h"
#include "entry.h"
#include "DarwinMain.h"
#include "Message.h"
#include "messagedef.h"
#include "IActionHandler.h"
#include "Singleton.cpp"

MainDispatcher::MainDispatcher()
{
	m_entryWindow = NULL;
	m_mainWindow = NULL;
}



MainDispatcher::~MainDispatcher(){

}

void MainDispatcher::StartAction(Message & act)
{
	switch(act.type()) {

	}
	m_handler->StartAction(act);
}

void MainDispatcher::OnEvent(Message& Msg)
{
	switch(Msg.type()) {
		case EVENT_SYSTEM_START: 
		{
			if(NULL == m_entryWindow) {
				m_entryWindow = Singleton<entry>::instance();
				m_entryWindow->SetHandler(this);
				SetObserver(m_entryWindow);
			}
			if(NULL == m_mainWindow) {
				m_mainWindow =  Singleton<DarwinMain>::instance();
				m_mainWindow->SetHandler(this);
				SetObserver(m_mainWindow);
			}
		}
	}

	BroadcastEvent(Msg);
}

