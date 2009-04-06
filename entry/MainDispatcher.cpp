///////////////////////////////////////////////////////////
//  MainDispatcher.cpp
//  Implementation of the Class MainDispatcher
//  Created on:      02-ËÄÔÂ-2009 18:03:22
//  Original author: Sunlight Kuo
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

//MainDispatcher* MainDispatcher::m_instance = 0;
MainDispatcher::MainDispatcher(){
	m_entryWindow	=	new entry();
	m_mainWindow = new DarwinMain();	
}



MainDispatcher::~MainDispatcher(){

}

void MainDispatcher::Start(){
	m_entryWindow->show();
}
/*
MainDispatcher* MainDispatcher::instance(){

	if (0 == m_instance) {
		m_instance = new MainDispatcher;
	}
	return m_instance;
//	
//	return 0;
}
*/
void MainDispatcher::Login(string& id, string& pw){
/*
	LOGIN para;
	memset(&para, 0, sizeof(LOGIN));
	memcpy(para.id, id.c_str(), ID_MAX_LEN);
	memcpy(para.pw, pw.c_str(), PW_MAX_LEN);
*/
	Stuff* stu = new Stuff();
	stu->SetID(id);
	stu->SetPassword(pw);
	Message* action = new Message(stu);
	action->setType(ACTION_LOGIN);
//	action->setData((byte*)(&para),sizeof(para));
	m_handler->StartAction(*action);
	delete action;
}

void MainDispatcher::StuffMgnt(){
	IEventObserver* StuffMgnt = Singleton<StuffManagement>::instance();
	StuffMgnt->SetHandler(m_handler);
	m_handler->SetObserver(StuffMgnt);

	Message* action = new Message();
	action->setType(ACTION_STUFFMGNT);
//	action->setData((byte*)NULL, 0);
	m_handler->StartAction(*action);
	delete action;
}

void MainDispatcher::Logoff(){
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
//	action->setData((byte*)NULL, 0);
	m_handler->StartAction(*action);
	delete action;

}
void MainDispatcher::SelfService(string& id, string& pw){

}

void MainDispatcher::OnEvent(Message& Msg) {
	switch(Msg.type()) {
		case EVENT_LOGGEDIN:
			{
				/*
				STUFF para;
				memcpy(&para, Msg.data(), sizeof(STUFF));
				*/
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