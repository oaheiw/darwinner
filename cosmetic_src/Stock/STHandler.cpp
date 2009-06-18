///////////////////////////////////////////////////////////
//  STHandler.cpp
//  Implementation of the Class STHandler
//  Created on:      15-ÁùÔÂ-2009 18:01:05
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "STHandler.h"
#include "messagedef.h"
#include "Message.h"
#include "IActionHandler.h"
#include "Singleton.h"
#include "StockWindow.h"

STHandler::STHandler()
:m_mainWindow(NULL){

}



STHandler::~STHandler(){
	delete m_mainWindow;
}


bool STHandler::CheckRight(uint32 actionId){
	return true;
}

void STHandler::StartAction(Message& act){
	if(act.isAction()) {
		if (!CheckRight(act.type()))
		{
			Message* ev = new Message(EVENT_RIGHTERROR);
			BroadcastEvent(*ev);
			delete ev;
			return;
		} 
		switch(act.type()) {

			default: break;
		}
		GetHandler()->StartAction(act);
	}
}

void STHandler::OnEvent(Message &ev)
{
	if(ev.isEvent()) {
		switch(ev.type()) {
			case EVENT_STOCKMGNT:
			{
				if(NULL == m_mainWindow) {
					m_mainWindow = Singleton<StockWindow>::instance();
					m_mainWindow->SetHandler(this);
					SetObserver(m_mainWindow);
				}
				break;
			}
			default:
				break;
		}
		BroadcastEvent(ev);
	}
}