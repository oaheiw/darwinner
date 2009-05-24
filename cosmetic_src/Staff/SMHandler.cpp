///////////////////////////////////////////////////////////
//  SMHandler.cpp
//  Implementation of the Class SMHandler
//  Created on:      08-Apr-2009 14:40:22 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "SMHandler.h"
#include "Message.h"
#include "messagedef.h"
#include "IActionHandler.h"
#include "StaffWindow.h"
#include "Singleton.h"
#include "JobTypeWidget.h"
#include "Job.h"
#include "Level.h"
#include "Status.h"
#include <algorithm>


SMHandler::SMHandler(){
	m_mainWindow = NULL;
	m_staffCache.clear();
}



SMHandler::~SMHandler(){

}


void SMHandler::Start(){

}


void SMHandler::StartAction(Message& act){
	if(act.isAction()) {
		switch(act.type())
		{
			case ACTION_GEALLSTAFF:
			{
				if(!m_staffCache.empty()) {
					Message* ev = new Message(EVENT_ALLSTAFF, &m_staffCache);
					BroadcastEvent(*ev);
					delete ev;
					return;
				} else {
					break;
				}
			}
			case ACTION_GETSTAFF:
			{
				uint32* id = static_cast<uint32*>(act.data());
				list<Staff>::iterator it = find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(*id));
				if(m_staffCache.end() != it) {
					Message* ev = new Message(EVENT_STAFF);
					ev->setData(&(*it));
					BroadcastEvent(*ev);
					delete ev;
					return;
				} else {
					break;
				}	
			}
			case ACTION_SETLEVELTYPE:
			{
				list<Level>* levels2update = static_cast<list<Level>*>(act.data());
				list<Level>* levels2remove = new list<Level>;
				for(list<Level>::iterator it = m_staffLevel.begin() ; m_staffLevel.end()!=it ; it++) {
					if(levels2update->end() == find_if(levels2update->begin(), levels2update->end(), Level::idMatcher(it->id()))) {
						levels2remove->push_back(*it);	
					} 
				}
				if(!levels2remove->empty()) {
					Message* remove = new Message(ACTION_REMOVELEVELTYPE, levels2remove);
					GetHandler()->StartAction(*remove);
					delete remove;
				}
				break;
			}
			case ACTION_SETJOBTYPE:
			{
				list<Job>* jobs2update = static_cast<list<Job>*>(act.data());
				list<Job>* jobs2remove = new list<Job>;
				for(list<Job>::iterator it = m_staffType.begin() ; m_staffType.end()!=it ; it++) {
					if(jobs2update->end() == 
						find_if(jobs2update->begin(), jobs2update->end(), Job::idMatcher(it->id()))) {
						jobs2remove->push_back(*it);	
					} 
				}
				if(!jobs2remove->empty()) {
					Message* remove = new Message(ACTION_REMOVEJOBTYPE, jobs2remove);
					GetHandler()->StartAction(*remove);
					delete remove;
				}
				break;
			}
			default: break;
		}
		GetHandler()->StartAction(act);
	}
}

void SMHandler::OnEvent(Message &ev)
{
	if(ev.isEvent()) {
		switch(ev.type())
		{
			case EVENT_STAFFMGNT:
			{
				if(NULL == m_mainWindow) {
					m_mainWindow = Singleton<StaffWindow>::instance();
					m_mainWindow->SetHandler(this);
					SetObserver(m_mainWindow);
				}
				break;
			}
			case EVENT_ALLSTAFF:
			{
				list<Staff>* temp = static_cast<list<Staff>*>(ev.data());
				m_staffCache = *temp;
				delete temp;
				ev.setData(&m_staffCache);
				break;
			}
			case EVENT_JOBTYPE:
			{
				list<Job>* temp = static_cast<list<Job>*>(ev.data());
				m_staffType = *temp;
				delete temp;
				ev.setData(&m_staffType);
				break;
			}
			case EVENT_LEVELTYPE:
			{
				list<Level>* temp = static_cast<list<Level>*>(ev.data());
				m_staffLevel = *temp;
				delete temp;
				ev.setData(&m_staffLevel);
				break;
			}
			case EVENT_STATUSTYPE:
			{
				list<Status>* temp = static_cast<list<Status>*>(ev.data());
				m_staffState  = *temp;
				delete temp;
				ev.setData(&m_staffState);
				break;
			}
			case EVENT_STAFFADDED:
			{
				Staff* addedStaff = static_cast<Staff*>(ev.data());
				 if(addedStaff->id() == SUPERUSERID)
				 	break;
				if(NULL != addedStaff) {
					list<Staff>::iterator it = 
						find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(addedStaff->id()));
					if(m_staffCache.end() == it) {
						m_staffCache.push_back(*addedStaff);
						ev.setData(&m_staffCache.back());
					}
					delete addedStaff;
				}
				break;
			}
			case EVENT_STAFFMODIFIED:
			{
				Staff* modifiedStaff = static_cast<Staff*>(ev.data());
				if(modifiedStaff->id() == SUPERUSERID)
				 	break;
				if(NULL != modifiedStaff) {
					list<Staff>::iterator it = 
						find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(modifiedStaff->id()));
					if(m_staffCache.end() != it) {
						m_staffCache.remove(*it);
						m_staffCache.push_back(*modifiedStaff);
						ev.setData(&m_staffCache.back());
						delete modifiedStaff;
					}
				}
				break;
			}
			case EVENT_STAFF:
			{
				Staff* staff = static_cast<Staff*>(ev.data());
				list<Staff>::iterator it = find_if(m_staffCache.begin(), m_staffCache.end(), 
					Staff::idMatcher(staff->id()));
				if(m_staffCache.end() == it) {
					m_staffCache.push_back(*staff);
					ev.setData(&m_staffCache.back());
				} 
				delete staff;
				break;
			}
			case EVENT_STAFFREMOVED:
			{
				uint32* id = static_cast<uint32*>(ev.data());
				list<Staff>::iterator it = find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(*id));
				if(m_staffCache.end() != it) { 
					m_staffCache.remove(*it);
				} else {
					ev.setData(NULL);
				}
				delete id;
				break;
			}
			default: break;
		}
		BroadcastEvent(ev);
	}
}

