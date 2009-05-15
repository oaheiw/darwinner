///////////////////////////////////////////////////////////
//  BmDbThread.cpp
//  Implementation of the Class BmDbThread
//  Created on:      05-ÎåÔÂ-2009 11:40:31
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "BmDbThread.h"
#include "Business.h"
#include "BusinessType.h"
#include "Message.h"
#include "messagedef.h"
#include <QByteArray>

BmDbThread::BmDbThread(QObject *parent, QThread::Priority priority)
:DbThread(parent, priority)
{
	setDbServer("QSQLITE", DBCONNECTION_BM, "", "", "", 0);
}




BmDbThread::~BmDbThread(){

}

void BmDbThread::WorkerThreadMain(Message& action)
{
	DBHEX("bm db thread processing action: ", action.type());
	switch(action.type()) {
		case ACTION_GETBUSINESSTYPE:
		{
			m_tempMsg = new Message(EVENT_BUSINESSTYPE, getBusinessTypes());
			break;
		}
		case ACTION_GETALLBUSINESS:
		{
			m_tempMsg = new Message(EVENT_ALLBUSINESS, getAllBusiness());
			break;
		}
		case ACTION_GETBUSINESS:
		{
			uint32* id = static_cast<uint32*>(action.data());
			m_tempMsg = new Message(EVENT_BUSINESS, getBusiness(*id));
			delete id;
			break;
		}
		case ACTION_GETBUSINESSPIC:
		{
			uint32* id = static_cast<uint32*>(action.data());
			m_tempMsg = new Message(EVENT_BUSINESSPIC, getImage(*id));
			delete id;
			break;
		}
		case ACTION_ADDBUSINESS:
		{
			Business* business = static_cast<Business*>(action.data());
			QByteArray* image = static_cast<QByteArray*>(action.data2());
			Business* addedBusiness = NULL;
			if(addBusiness(business)) {
				addedBusiness = getBusiness(business->id());
			}
			m_tempMsg = new Message(EVENT_ADDBUSINESS, addedBusiness);
			if(NULL != image && !image->isEmpty() && addedBusiness->id() != 0) {
				if(addImage(addedBusiness->id(), *image))
					m_tempMsg->setData2(getImage(addedBusiness->id()));
			}
			delete business;
			break;
		}
		case ACTION_REMOVEBUSINESS:
		{
			uint32* id = static_cast<uint32*>(action.data());
			int* result = new int(ERROR_NO_ERROR);
			if(!removeBusiness(*id))
				*result = ERROR_REMOVE;
			m_tempMsg = new Message(EVENT_REMOVEBUSINESS, result);
			delete id;
			break;
		}
		case ACTOIN_MODIFYBUSINESS:
		{
			Business* toModify = static_cast<Business*>(action.data());
			QByteArray* image = static_cast<QByteArray*>(action.data2());
			Business* modified = NULL;
			if(modifyBusiness(toModify)) {
				modified = getBusiness(toModify->id());
			}
			m_tempMsg = new Message(EVENT_MODIFYBUSINESS, modified);
			if(NULL != image && !image->isEmpty() && modified->id() != 0) {
				if(addImage(modified->id(), *image))
					m_tempMsg->setData2(getImage(modified->id()));
			}
			delete toModify;
			break;
		}
		case ACTION_VIEWBUSINESSRECORD:
		{
			break;
		}
		case ACTION_SETBUSINESSTYPE:
		{
			list<BusinessType>* toSet = static_cast<list<BusinessType>*>(action.data());
			list<BusinessType>* result = new list<BusinessType>;
			list<BusinessType>::iterator it = toSet->begin();
			while(toSet->end() != it) {
				if(!addBusinessType(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete toSet;
			m_tempMsg = new Message(EVENT_SETBUSINESSTYPE, result);
			break;
		}
		case ACTION_REMOVEBUSINESSTYPE:
		{
			list<BusinessType>* toRemove = static_cast<list<BusinessType>*>(action.data());
			list<BusinessType>* result = new list<BusinessType>;
			list<BusinessType>::iterator it = toRemove->begin();
			while(toRemove->end() != it) {
				if(!addBusinessType(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete toRemove;
			m_tempMsg = new Message(EVENT_REMOVEBUSINESS, result);
			break;

		}
		default: break;	
	}
	if(NULL != m_tempMsg) {
		postEvent(m_tempMsg, EventDb);
		m_tempMsg = NULL;
	}
}

bool BmDbThread::addBusiness(Business* data){

	return false;
}


bool BmDbThread::addBusinessType(BusinessType* data){

	return false;
}


bool BmDbThread::addImage(uint32 id, QByteArray& data){

	return false;
}


Business* BmDbThread::getBusiness(uint32 id){

	return  NULL;
}


list<BusinessType>* BmDbThread::getBusinessTypes(){

	return  NULL;
}


QByteArray* BmDbThread::getImage(uint32 id){

	return  NULL;
}


bool BmDbThread::modifyBusiness(Business* data){

	return false;
}


bool BmDbThread::modifyBusinessType(BusinessType* data){

	return false;
}


bool BmDbThread::removeBusiness(uint32 id){

	return false;
}


bool BmDbThread::removeBusinessType(uint32 id){

	return false;
}


bool BmDbThread::removeImage(uint32 id){

	return false;
}



list<Business>* BmDbThread::getAllBusiness(){

	return  NULL;
}
