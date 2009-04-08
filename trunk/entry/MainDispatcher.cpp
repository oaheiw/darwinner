///////////////////////////////////////////////////////////
//  MainDispatcher.cpp
//  Implementation of the Class MainDispatcher
//  Created on:      02-Apr-2009 18:03:22
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "MainDispatcher.h"
#include "entry.h"
#include "DarwinMain.h"
#include "Worker.h"
#include "Message.h"
#include "Singleton.cpp"
#include "StaffManagement.h"
#include "WorkerFactory.h"
#include "Staff.h"
#include "IActionHandler.h"
#include "messagedef.h"

MainDispatcher::MainDispatcher()
{
	m_entryWindow = new entry();
	m_entryWindow->SetHandler(this);
	SetObserver(m_entryWindow);
	
	m_mainWindow = new DarwinMain();
	m_mainWindow->SetHandler(this);
	SetObserver(m_mainWindow);
}



MainDispatcher::~MainDispatcher(){

}

void MainDispatcher::Start(){
	Message start;
	start.setType(EVENT_SYSTEM_START);
	BroadcastEvent(start);
}

void MainDispatcher::StartAction(Message & act)
{
	switch(act.type()) {
		case ACTION_STUFFMGNT:
		{
			DUIObserver* StaffMgnt = Singleton<StaffManagement>::instance();
			StaffMgnt->SetHandler(this);
			SetObserver(StaffMgnt);			

		}
	}
	m_handler->StartAction(act);
}
void MainDispatcher::Login(string& id, string& pw)
{

}

void MainDispatcher::StaffMgnt(){

}

void MainDispatcher::Logoff(){

}
void MainDispatcher::SelfService(string& id, string& pw){

}

void MainDispatcher::OnEvent(Message& Msg)
{
	BroadcastEvent(Msg);
}
