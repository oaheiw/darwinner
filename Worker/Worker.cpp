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
#include "ThreadDatabase.h"
#include <QThread>
#include "TEvent.h"
#include "Message.h"
#include "dbquery.h"
//#include <io.h>
#include <fstream>
#include <iostream>
//#include <stdio.h>
//#include <string.h>

using namespace std;
Worker::Worker(QObject *parent )
:QObject(parent)
{
		m_databaseThread = new ThreadDatabase(this);
}



Worker::~Worker(){

}

void Worker::StartAction(Message& Action) {
	switch(Action.type()) {
	case ACTION_SYSTEM_START:
		{
			bool exist;
			int length= 0;
			char* SQLiteMark;
			int isSQLite = -1;
			fstream testfile;
			testfile.open (DBFILE, fstream::in | fstream::out | fstream::app | fstream::binary);
			exist = testfile.is_open();
			if(exist) {
			  testfile.seekg (0, ios::end);
			  length = testfile.tellg();
			  testfile.seekg (0, ios::beg);

			  SQLiteMark = new char [SQLITEMARKLEN];
			  memset(SQLiteMark, 0, SQLITEMARKLEN);
			  testfile.read (SQLiteMark, SQLITEMARKLEN);
			  isSQLite = memcmp(SQLiteMark, SQLITEMARK, SQLITEMARKLEN);
			  testfile.close();
			}
			  
			if(!exist | 0 == length | 0 != isSQLite) {//first time running
					remove(DBFILE);
					cout<<"dbfile corrupt or not exists. create a brand new one."<<endl;
					Message* ev = new Message(ACTION_INIT);
					m_databaseThread->QueueAction(*ev);
					delete ev;
					break;
				} else {//database exists
					testfile.close();
					Message* ev = new Message(EVENT_SYSTEM_START);
					BroadcastEvent(*ev);
					delete ev;
				}
			break;
		}
		case ACTION_STAFFMGNT:
		{
			Message* ev = new Message(EVENT_STAFFMGNT);
			BroadcastEvent(*ev);
			delete ev;
			break;
		}
		case ACTION_LOGOFF:
		{
			Message* ev = new Message(EVENT_LOGGEDOFF);
			BroadcastEvent(*ev);
			delete ev;
			break;
		}
		case ACTION_EXIT:
		{
			m_databaseThread->quit();
			Message* ev = new Message(EVENT_EXIT);
			BroadcastEvent(*ev);
			delete ev;
			break;
		}
		case ACTION_MAINMENU:
		{
			m_databaseThread->quit();
			Message* ev = new Message(EVENT_MAINMENU);
			BroadcastEvent(*ev);
			delete ev;
			break;
		}
		default:
		{
			m_databaseThread->QueueAction(Action);
			break;
		}
	}
}

void Worker::IncomingEvent(Message& ev) {
	BroadcastEvent(ev);
}

bool Worker::event ( QEvent * e ) {
	switch(e->type()) {
		case EventDb:
			{
				Message* ev = dynamic_cast<TEvent*>(e)->data();
				BroadcastEvent(*ev);
			}
	}
	return true;
}
