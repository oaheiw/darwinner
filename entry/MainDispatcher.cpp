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
#include "StuffManagement.h"
#include "WorkerFactory.h"
#include "Stuff.h"

MainDispatcher::MainDispatcher(){
	m_entryWindow	=	new entry();
	m_mainWindow = new DarwinMain();	
}



MainDispatcher::~MainDispatcher(){

}

void MainDispatcher::Start(){
	m_entryWindow->show();
}

void MainDispatcher::Login(string& id, string& pw)
{
	Stuff* stu = new Stuff();
	stu->SetID(id);
	stu->SetPassword(pw);
	Message* action = new Message(stu);
	action->setType(ACTION_LOGIN);
	m_handler->StartAction(*action);
	delete action;
}

void MainDispatcher::StuffMgnt(){
	IEventObserver* StuffMgnt = Singleton<StuffManagement>::instance();
	StuffMgnt->SetHandler(m_handler);
	m_handler->SetObserver(StuffMgnt);

	Message* action = new Message();
	action->setType(ACTION_STUFFMGNT);
	m_handler->StartAction(*action);
	delete action;
}

void MainDispatcher::Logoff(){
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
	m_handler->StartAction(*action);
	delete action;

}
void MainDispatcher::SelfService(string& id, string& pw){

}

void MainDispatcher::OnEvent(Message& Msg) {
	switch(Msg.type()) {
		case EVENT_LOGGEDIN:
			{
				Stuff* Logged = (Stuff*)(Msg.data());
				Singleton<Stuff>::instance()->SetName(Logged->Name());
				m_entryWindow->close();
				m_mainWindow->show();
				m_mainWindow->ui.labelInfo->setText(QString::fromLocal8Bit("ÄúºÃ£¬") + QString::fromLocal8Bit(Singleton<Stuff>::instance()->Name().c_str()));
				break;
			}
		case EVENT_STUFFMGNT:
			{
				m_mainWindow->hide();
				Singleton<StuffManagement>::instance()->show();
				break;
			}
			case EVENT_LOGGEDOFF:
			{
				m_mainWindow->close();
				m_entryWindow->show();
				break;
			}
		case EVENT_EXIT:
		{
				m_mainWindow->close();
				m_entryWindow->close();
			break;
		}
		default:
			break;
	}
}