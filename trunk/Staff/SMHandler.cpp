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
#include "StaffManagementUI.h"
#include "Singleton.cpp"
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
					Message* ev = new Message(EVENT_STAFF, &m_staffCache);
					ev->setData(&(*it));
					BroadcastEvent(*ev);
					delete ev;
					return;
				} else {
					break;
				}	
			}
		}
	}
	m_handler->StartAction(act);
}

void SMHandler::OnEvent(Message &ev)
{
	if(ev.isEvent()) {
		switch(ev.type())
		{
			case EVENT_STAFFMGNT:
			{
				if(NULL == m_mainWindow) {
					m_mainWindow = Singleton<StaffManagementUI>::instance();
					m_mainWindow->SetHandler(this);
					SetObserver(m_mainWindow);
				}
				break;
			}
			case EVENT_ALLSTAFF:
			{
				list<Staff>* temp = static_cast<list<Staff>*>(ev.data());
				m_staffCache = *(temp);
				delete temp;
				ev.setData(&m_staffCache);
				break;
			}
			case EVENT_JOBTYPE:
			{
				list<Job>* temp = static_cast<list<Job>*>(ev.data());
				m_staffType = *(temp);
				delete temp;
				ev.setData(&m_staffType);
				break;
			}
			case EVENT_LEVELTYPE:
			{
				list<Level>* temp = static_cast<list<Level>*>(ev.data());
				m_staffLevel = *(temp);
				delete temp;
				ev.setData(&m_staffLevel);
				break;
			}
			case EVENT_STATUSTYPE:
			{
				list<Status>* temp = static_cast<list<Status>*>(ev.data());
				m_staffState  = *(temp);
				delete temp;
				ev.setData(&m_staffState);
				break;
			}

			case EVENT_STAFFADDED:
			{
				Staff* addedStaff = static_cast<Staff*>(ev.data());
				if(NULL != addedStaff) {
					list<Staff>::iterator it = find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(addedStaff->ID()));
					if(m_staffCache.end() == it) {
						m_staffCache.push_back(*addedStaff);
						ev.setData(&m_staffCache.back());
					} else {
						ev.setData(NULL);
					}
					delete addedStaff;
				}
				break;
			}
			case EVENT_STAFFMODIFIED:
			{
				Staff* modifiedStaff = static_cast<Staff*>(ev.data());
				if(NULL != EVENT_STAFFMODIFIED) {
					list<Staff>::iterator it = find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(modifiedStaff->ID()));
					if(m_staffCache.end() != it) {
						m_staffCache.remove(*it);
					}
					m_staffCache.push_back(*modifiedStaff);
					ev.setData(&m_staffCache.back());
					delete modifiedStaff;
				}
				break;
			}

			case EVENT_STAFF:
			{
				Staff* staff = static_cast<Staff*>(ev.data());
				list<Staff>::iterator it = find_if(m_staffCache.begin(), m_staffCache.end(), Staff::idMatcher(staff->ID()));
				if(m_staffCache.end() == it) {
					m_staffCache.push_back(*staff);
					ev.setData(&m_staffCache.back());
				} else {
					ev.setData(NULL);
				}
				delete staff;
				break;
			}
		}
		BroadcastEvent(ev);
	}
}
