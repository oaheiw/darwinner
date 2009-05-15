#include "BMHandler.h"
#include "Message.h"
#include "messagedef.h"
#include "IActionHandler.h"
#include "BusinessWindow.h"
#include "Singleton.h"
#include <algorithm>

BMHandler::BMHandler()
{
	m_mainWindow = NULL;
	m_businessCache.clear();
}

BMHandler::~BMHandler()
{

}

void BMHandler::StartAction(Message& act){
	if(act.isAction()) {
		switch(act.type())
		{
	
		}
	}
	m_handler->StartAction(act);
}

void BMHandler::OnEvent(Message &ev)
{
	if(GROUP_BUSINESSMGNT != ev.group()) return;
	if(ev.isEvent()) {
		switch(ev.type())
		{
			case EVENT_BUSINESSMGNT:
			{
				if(NULL == m_mainWindow) {
					m_mainWindow = Singleton<BusinessWindow>::instance();
					m_mainWindow->SetHandler(this);
					SetObserver(m_mainWindow);
				}
				break;
			}
		}
		BroadcastEvent(ev);
	}
}




void BMHandler::checkRights(Message* action){

}
