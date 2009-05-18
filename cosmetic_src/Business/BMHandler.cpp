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
		switch(act.type()) {
			case ACTION_GETALLBUSINESS:
				{
					if(!m_businessCache.empty()) {
						Message* ev = new Message(EVENT_ALLBUSINESS, &m_businessCache);
						BroadcastEvent(*ev);
						delete ev;
						return;
					} else {
						break;
					}
				}
			case ACTION_GETBUSINESS:
				{
					uint32* id = static_cast<uint32*>(act.data());
					list<Business>::iterator it = 
						find_if(m_businessCache.begin(), m_businessCache.end(), Business::BusinessIdMatcher(*id));
					if(m_businessCache.end() != it) {
						Message* ev = new Message(EVENT_BUSINESS, &(*it));
						BroadcastEvent(*ev);
						delete ev;
						return;
					} else {
						break;
					}	
				}
			case ACTION_SETBUSINESSTYPE:
				{
					list<BusinessType>* types2update = static_cast<list<BusinessType>*>(act.data());
					list<BusinessType>* types2remove = new list<BusinessType>;

					for(list<BusinessType>::iterator it = m_businessTypeCache.begin() ; m_businessTypeCache.end()!=it ; it++) {
						if(types2update->end() == find_if(types2update->begin(), types2update->end(), 
						BusinessType::BusinessTypeIdMatcher(it->getId()))) {
							types2remove->push_back(*it);	
						} 
					}

					if(!types2remove->empty()) {
						Message* remove = new Message(ACTION_REMOVEBUSINESSTYPE, types2remove);
						m_handler->StartAction(*remove);
						delete remove;
					}
					break;
				}
			default: break;
		}
		m_handler->StartAction(act);
	}
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
			case EVENT_ALLBUSINESS:
				{
					list<Business>* data = static_cast<list<Business>*>(ev.data());
					m_businessCache = *data;
					delete data;
					ev.setData(&m_businessCache);
					break;
				}
			case EVENT_BUSINESSTYPE:
				{
					list<BusinessType>* data = static_cast<list<BusinessType>*>(ev.data());
					m_businessTypeCache = *data;
					delete data;
					ev.setData(&m_businessTypeCache);
					break;
				}
			case EVENT_ADDBUSINESS:
				{
					Business* added = static_cast<Business*>(ev.data());
					if(NULL != added) {
						list<Business>::iterator it = find_if(m_businessCache.begin(), m_businessCache.end(), 
							Business::BusinessIdMatcher(added->id()));
						if(m_businessCache.end() == it) {
							m_businessCache.push_back(*added);
							ev.setData(&m_businessCache.back());
						}
						delete added;
					}
					break;
				}
			case EVENT_MODIFYBUSINESS:
				{
					Business* modified = static_cast<Business*>(ev.data());
					if(NULL != modified) {
						list<Business>::iterator it = find_if(m_businessCache.begin(), m_businessCache.end(), 
							Business::BusinessIdMatcher(modified->id()));
						if(m_businessCache.end() != it) {
							m_businessCache.remove(*it);
							m_businessCache.push_back(*modified);
							ev.setData(&m_businessCache.back());
						}
						delete modified;
					}
					break;
				}
			case EVENT_BUSINESS:
				{
					Business* data = static_cast<Business*>(ev.data());
					if(NULL != data) {
						list<Business>::iterator it = find_if(m_businessCache.begin(), m_businessCache.end(), 
							Business::BusinessIdMatcher(data->id()));
						if(m_businessCache.end() == it) {
							m_businessCache.push_back(*data);
							ev.setData(&m_businessCache.back());
						}
						delete data;
					}
					break;
				}
			case EVENT_REMOVEBUSINESS:
				{
					uint32* id = static_cast<uint32*>(ev.data());
					list<Business>::iterator it = find_if(m_businessCache.begin(), m_businessCache.end(), 
						Business::BusinessIdMatcher(*id));
					if(m_businessCache.end() != it) {
						m_businessCache.remove(*it);
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




void BMHandler::checkRights(Message* action){

}
