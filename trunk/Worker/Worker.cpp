///////////////////////////////////////////////////////////
//  Processer.cpp
//  Implementation of the Class Processer
//  Created on:      02-Apr-2009 18:10:13
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "common.h"
#include "Worker.h"
#include "Message.h"
#include "Stuff.h"
#include "ThreadDatabase.h"
#include <QThread>
#include "TEvent.h"

Worker::Worker(QObject *parent )
:QObject(parent)
{
//	QEvent::registerEventType(WorkerEventType::Db);
//	QEvent::registerEventType(WorkerEventType::Net);
	m_databaseThread = new ThreadDatabase(this); 
	int r = connect(m_databaseThread, SIGNAL(hasEvent(Message &)), this, SLOT(IncomingEvent(Message &)));//, Qt::DirectConnection);
}



Worker::~Worker(){

}

void Worker::StartAction(Message& Action) {
	m_databaseThread->QueueAction(Action);
}

void Worker::IncomingEvent(Message& ev) {
	BroadcastEvent(ev);
}

bool Worker::event ( QEvent * e ) {
	switch(e->type()) {
		case WorkerEventType::Db:
			{
				Message* ev = dynamic_cast<TEvent*>(e)->data();
				BroadcastEvent(*ev);
			}
	}
	return true;
}