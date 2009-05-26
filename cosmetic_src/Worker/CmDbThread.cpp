///////////////////////////////////////////////////////////
//  CmDbThread.cpp
//  Implementation of the Class CmDbThread
//  Created on:      26-ÎåÔÂ-2009 16:48:51
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "CmDbThread.h"
#include "Customer.h"
#include "CustomerLevel.h"
#include "Message.h"
#include "messagedef.h"
#include <QByteArray>
#include <QSqlQuery>
#include <QVariant>
#include "dbquery.h"



CmDbThread::CmDbThread(QObject *parent, QThread::Priority priority)
:DbThread(parent, priority)
{
	setDbServer("QSQLITE", DBCONNECTION_CM, "", "", "", 0);
}


CmDbThread::~CmDbThread(){

}


bool CmDbThread::addCustomer(Customer* data){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBHEX("adding customer...", data->name());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));

	q.prepare(INSERTINTO_CUSTOMER);

	q.bindValue(":password", data->password().c_str());
	q.bindValue(":name", data->name().c_str());
	q.bindValue(":sex", data->sex());
	q.bindValue(":levelid", data->getLevel());
	q.bindValue(":cell", data->cell().c_str());
	q.bindValue(":phone", data->phone().c_str());
	q.bindValue(":address", data->address().c_str());
	q.bindValue(":description", data->description().c_str());
	q.bindValue(":deposit", data->getDeposit());

	r = q.exec();
	if(r) {
		q.exec(SELECT_MAX_CUSTOMERID);
		if(q.next())
			data->setid(q.value(0).toUInt());
			QString setpw = QString(UPDATE_CUSTOMERPASWORD_BYID).arg(data->id()).arg(data->id());
			q.exec(setpw);
	}
	closeDb();
	DBDEC("add customer completed:", data->id());
	return r;
}


bool CmDbThread::addCustomerLevel(CustomerLevel* data){

	return false;
}


bool CmDbThread::addImage(uint32 id, QByteArray& data){

	return false;
}


list<Customer>* CmDbThread::getAllCustomer(){

	return  NULL;
}


Customer* CmDbThread::getCustomer(uint32 id){

	return  NULL;
}


list<CustomerLevel>* CmDbThread::getCustomerLevels(){

	return  NULL;
}


QByteArray* CmDbThread::getImage(uint32 id){

	return  NULL;
}


bool CmDbThread::modifyCustomer(Customer* data){

	return false;
}


bool CmDbThread::modifyCustomerLevel(CustomerLevel* data){

	return false;
}


bool CmDbThread::removeCustomer(uint32 id){

	return false;
}


bool CmDbThread::removeCustomerLevel(uint32 id){

	return false;
}


bool CmDbThread::removeImage(uint32 id){

	return false;
}


void CmDbThread::WorkerThreadMain(Message& action){
	DBHEX("customer db thread processing action: ", action.type());
	switch(action.type()) {
		case ACTION_GETCUSTOMERLEVEL:
			{
				m_tempMsg = new Message(EVENT_CUSTOMERLEVEL, getCustomerLevels());
				break;
			}
		case ACTION_GETALLCUSTOMER:
			{
				m_tempMsg = new Message(EVENT_ALLCUSTOMERS, getAllCustomer());
				break;
			}
		case ACTION_GETCUSTOMER:
			{
				uint32* id = static_cast<uint32*>(action.data());
				m_tempMsg = new Message(EVENT_CUSTOMER, getCustomer(*id));
				delete id;
				break;
			}
		case ACTION_GETCUSTOMERPIC:
			{
				uint32* id = static_cast<uint32*>(action.data());
				m_tempMsg = new Message(EVENT_CUSTOMERPIC, getImage(*id));
				delete id;
				break;
			}
		case ACTION_ADDCUSTOMER:
			{
				Customer* toAdd = static_cast<Customer*>(action.data());
				QByteArray* image = static_cast<QByteArray*>(action.data2());
				Customer* added = NULL;
				m_tempMsg = new Message(EVENT_ADDCUSTOMER);
				if(addCustomer(toAdd)) {
					added = getCustomer(toAdd->id());
					m_tempMsg->setData(added);
					if(NULL != added && NULL != image && !image->isEmpty()) {
						if(addImage(added->id(), *image))
							m_tempMsg->setData2(getImage(added->id()));
					}
				}
				delete toAdd;
				break;
			}
		case ACTION_REMOVECUSTOMER:
			{
				uint32* id = static_cast<uint32*>(action.data());
				uint32* result = new uint32(*id);
				if(!removeCustomer(*id))
					*result = 0;
				m_tempMsg = new Message(EVENT_REMOVECUSTOMER, result);
				delete id;
				break;
			}
		case ACTOIN_MODIFYCUSTOMER:
			{
				Customer* toModify = static_cast<Customer*>(action.data());
				QByteArray* image = static_cast<QByteArray*>(action.data2());
				Customer* modified = NULL;
				m_tempMsg = new Message(EVENT_MODIFYCUSTOMER);
				if(modifyCustomer(toModify)) {
					modified = getCustomer(toModify->id());
					m_tempMsg->setData(modified);
					if(NULL != image && !image->isEmpty() && toModify->id() != 0) {
						if(addImage(modified->id(), *image))
							m_tempMsg->setData2(getImage(modified->id()));
					}
				}
				delete toModify;
				break;
			}
		case ACTION_VIEWCONSUMERECORD:
			{
				break;
			}
		case ACTION_SETCUSTOMERLEVEL:
			{
				list<CustomerLevel>* toSet = static_cast<list<CustomerLevel>*>(action.data());
				list<CustomerLevel>* result = new list<CustomerLevel>;
				list<CustomerLevel>::iterator it = toSet->begin();
				while(toSet->end() != it) {
					if(!addCustomerLevel(&(*it)))
						result->push_back(*it);
					it++;
				}
				delete toSet;
				m_tempMsg = new Message(EVENT_SETCUSTOMERLEVEL, result);
				break;
			}
		case ACTION_REMOVECUSTOMELEVEL:
			{
				list<CustomerLevel>* toRemove = static_cast<list<CustomerLevel>*>(action.data());
				list<CustomerLevel>* result = new list<CustomerLevel>;
				list<CustomerLevel>::iterator it = toRemove->begin();
				while(toRemove->end() != it) {
					if(!removeCustomerLevel(it->getId()))
						result->push_back(*it);
					it++;
				}
				delete toRemove;
				m_tempMsg = new Message(EVENT_REMOVECUSTOMELEVEL, result);
				break;

			}
		default: break;	
	}
	if(NULL != m_tempMsg) {
		postEvent(m_tempMsg, EventDb);
		m_tempMsg = NULL;
	}
}