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
#include "Singleton.h"
#include <algorithm>
#include "CustomerWindow.h"

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
			case EVENT_CUSTOMERMGNT:
				{
					if(NULL == m_mainWindow) {
						m_mainWindow = Singleton<CustomerWindow>::instance();
						m_mainWindow->SetHandler(this);
						SetObserver(m_mainWindow);
					}
					break;
				}
			case EVENT_ALLCUSTOMERS:
				{
					list<Customer>* data = 
						static_cast<list<Customer>*>(ev.data());
					m_customerCache = *data;
					delete data;
					ev.setData(&m_customerCache);
					break;
				}
			case EVENT_CUSTOMERLEVEL:
				{
					list<CustomerLevel>* data = 
						static_cast<list<CustomerLevel>*>(ev.data());
					m_customerLevelCache = *data;
					delete data;
					ev.setData(&m_customerLevelCache);
					break;
				}
			case EVENT_ADDCUSTOMER:
				{
					Customer* added = static_cast<Customer*>(ev.data());
					if(NULL != added) {
						list<Customer>::iterator it = 
							find_if(m_customerCache.begin(), 
							m_customerCache.end(), 
							Customer::CustomerIdMatcher(added->id()));
						if(m_customerCache.end() == it) {
							m_customerCache.push_back(*added);
							ev.setData(&m_customerCache.back());
						}
						delete added;
					}
					break;
				}
			case EVENT_MODIFYCUSTOMER:
				{
					Customer* modified = static_cast<Customer*>(ev.data());
					if(NULL != modified) {
						list<Customer>::iterator it = 
							find_if(m_customerCache.begin(), 
							m_customerCache.end(), 
							Customer::CustomerIdMatcher(modified->id()));
						if(m_customerCache.end() != it) {
							m_customerCache.remove(*it);
							m_customerCache.push_back(*modified);
							ev.setData(&m_customerCache.back());
						}
						delete modified;
					}
					break;
				}
			case EVENT_CUSTOMER:
				{
					Customer* data = static_cast<Customer*>(ev.data());
					if(NULL != data) {
						list<Customer>::iterator it = 
							find_if(m_customerCache.begin(), 
							m_customerCache.end(), 
							Customer::CustomerIdMatcher(data->id()));
						if(m_customerCache.end() == it) {
							m_customerCache.push_back(*data);
							ev.setData(&m_customerCache.back());
						}
						delete data;
					}
					break;
				}
			case EVENT_REMOVECUSTOMER:
				{
					uint32* id = static_cast<uint32*>(ev.data());
					if(0 != *id) {
							list<Customer>::iterator it = 
							find_if(m_customerCache.begin(), 
							m_customerCache.end(), 
							Customer::CustomerIdMatcher(*id));
						if(m_customerCache.end() != it) {
							m_customerCache.remove(*it);
						} else {
							ev.setData(NULL);
						}
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


void CMHandler::StartAction(Message& act){
	if(act.isAction()) {
		if (!CheckRight(act.type())){
			Message* ev = new Message(EVENT_RIGHTERROR);
			BroadcastEvent(*ev);
			delete ev;
			return;
		} 
		switch(act.type()) {
			case ACTION_GETALLCUSTOMER:
				{
					if(!m_customerCache.empty()) {
						Message* ev = new Message(EVENT_ALLCUSTOMERS, 
							&m_customerCache);
						BroadcastEvent(*ev);
						delete ev;
						return;
					} else {
						break;
					}
				}
			case ACTION_GETCUSTOMER:
				{
					uint32* id = static_cast<uint32*>(act.data());
					list<Customer>::iterator it = 
						find_if(m_customerCache.begin(), m_customerCache.end(), 
						Customer::CustomerIdMatcher(*id));
					if(m_customerCache.end() != it) {
						Message* ev = new Message(EVENT_CUSTOMER, &(*it));
						BroadcastEvent(*ev);
						delete ev;
						return;
					} else {
						break;
					}	
				}
			case ACTION_SETCUSTOMERLEVEL:
				{
					list<CustomerLevel>* types2update = 
						static_cast<list<CustomerLevel>*>(act.data());
					list<CustomerLevel>* types2remove = new list<CustomerLevel>;

					for(list<CustomerLevel>::iterator it = 
						m_customerLevelCache.begin() 
						; m_customerLevelCache.end()!=it 
						; it++) {
						if(types2update->end() == 
							find_if(types2update->begin(), types2update->end(), 
							CustomerLevel::CustomerLevelIdMatcher(it->getId()))){
								types2remove->push_back(*it);	
						} 
					}

					if(!types2remove->empty()) {
						Message* remove = new Message(ACTION_REMOVECUSTOMELEVEL, 
							types2remove);
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