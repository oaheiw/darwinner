///////////////////////////////////////////////////////////
//  CMHandler.cpp
//  Implementation of the Class CMHandler
//  Created on:      24-ÎåÔÂ-2009 16:59:43
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "CMHandler.h"
#include "common.h"
#include "messagedef.h"
#include "Message.h"
#include "IActionHandler.h"

CMHandler::CMHandler()
:m_mainWindow(NULL)
{
	m_customerCache.clear();
	m_customerLevelCache.clear();
}



CMHandler::~CMHandler(){
	delete m_mainWindow;
}

bool CMHandler::CheckRight(uint32 actionId){
	return true;
}

void CMHandler::OnEvent(Message& ev){
	if(ev.isEvent()) {
		switch(ev.type())
		{

		}
		BroadcastEvent(ev);
	}
}


void CMHandler::StartAction(Message& act){
	if(act.isAction()) {
		if (!CheckRight(act.type())){
			Message* ev = new Message(EVENT_RIGHTERROR);
			BroadcastEvent(*ev);
			delete ev;
			return;
		} 
		switch(act.type()) {

		}
		GetHandler()->StartAction(act);
	}
}