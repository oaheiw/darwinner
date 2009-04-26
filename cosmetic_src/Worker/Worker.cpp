///////////////////////////////////////////////////////////
//  Processer.cpp
//  Implementation of the Class Processer
//  Created on:      02-Apr-2009 18:10:13
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "common.h"
#include "messagedef.h"
#include "Worker.h"
#include "Staff.h"
#include "SmDbThread.h"
#include "CommonDbThread.h"
#include <QThread>
#include "TEvent.h"
#include "Message.h"

using namespace std;
Worker::Worker(QObject *parent )
:QObject(parent)
{
	m_commonDbThread = new CommonDbThread(this, QThread::HighPriority);
	m_smDbThread = new SmDbThread(this, QThread::HighPriority);
}

Worker::~Worker(){
	delete m_smDbThread;
}

void Worker::StartAction(Message& Action) {
	DBINFO("worker catch one action: ", Action.type());
	if(GROUP_COMMON == Action.group()) {
		switch(Action.type()) {
			case ACTION_EXIT:
			{
				m_smDbThread->quit();
				m_commonDbThread->quit();
				Message* ev = new Message(EVENT_EXIT);
				BroadcastEvent(*ev);
				delete ev;
				break;
			}
			case ACTION_MAINMENU:
			{
				m_smDbThread->quit();
				Message* ev = new Message(EVENT_MAINMENU);
				BroadcastEvent(*ev);
				delete ev;
				break;
			}
			default:
			{
				m_commonDbThread->QueueAction(Action);
				break;
			}

		}
	}
	else if (GROUP_STAFFMGNT == Action.group()) {
		switch(Action.type()) {
			case ACTION_STAFFMGNT:
			{
				Message* ev = new Message(EVENT_STAFFMGNT);
				BroadcastEvent(*ev);
				delete ev;
				break;
			}
			default:
			{
				m_smDbThread->QueueAction(Action);
				break;
			}
		}
	}
}

bool Worker::event(QEvent * e) {
	switch(e->type()) {
		case EventDb:
			{
				Message* ev = dynamic_cast<TEvent*>(e)->data();
				if(!ev->isEvent()) return true;
				switch(ev->type()) {

				}
				BroadcastEvent(*ev);
			}
	}
	return true;
}
