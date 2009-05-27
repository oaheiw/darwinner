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
		if(q.isActive())
			data->setid(q.value(0).toUInt());
			QString setpw = QString(UPDATE_CUSTOMERPASWORD_BYID)
				.arg(data->id()).arg(data->id());
			q.exec(setpw);
	}
	closeDb();
	DBDEC("add customer completed:", data->id());
	return r;
}


bool CmDbThread::addCustomerLevel(CustomerLevel* data){
	bool r = false;
	if(0 == data->getId()) {//only 0 id data should be added
		if(!openDb(DBNAME)) {
			return r;
		}
		DBHEX("adding customer level ...", data->getName());
		QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
		q.prepare(INSERTINTO_CUSTOMERLEVEL_TABLE);
		q.bindValue(":name", data->getName().c_str());
		q.bindValue(":requireconsume", data->getTotalCosume());
		q.bindValue(":discount", data->getTotalCosume());
		q.bindValue(":description", data->getDescription().c_str());
		r = q.exec();
		DBDEC("add customer level completed", r);
		closeDb();
	} else {//data id other than 0 should be modified
		r = modifyCustomerLevel(data);
	}
	return r;
}


bool CmDbThread::addImage(uint32 id, QByteArray& data){
	bool r = true;
	if(!openDb(DBNAME)) {
		return r;
	}

	DBDEC("setting customer image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));

	QString check = QString(CHECK_CUSTOMERIMAGE_BYID).arg(id);
	if(q.exec(check)) {
		if(q.isActive())
			r = q.exec(QString(DELETE_CUSTOMERIMAGE).arg(id));
	}
	if(r) {
		q.prepare(INSERT_CUSTOMERIMAGE);
		q.bindValue(":id", id);
		q.bindValue(":data", data, QSql::Binary | QSql::In);
		r = q.exec();
	}
	closeDb();
	DBDEC("set customer image complete", r);
	return r;
}


list<Customer>* CmDbThread::getAllCustomer(){
	list<Customer>* r = new list<Customer>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}

	DBHEX("geting all customer...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
	q.exec(SELECT_CUSTOMER_ALL);
	Customer temp;

	while (q.next()) {
		temp.setid(q.value(0).toUInt());
		temp.setpassword(q.value(1).toByteArray().data());
		temp.setname(q.value(1).toByteArray().data());
		temp.setsex(q.value(2).toUInt());
		temp.setLevel(q.value(3).toUInt());
		temp.setcell(q.value(4).toByteArray().data());
		temp.setphone(q.value(5).toByteArray().data());
		temp.setaddress(q.value(6).toByteArray().data());
		temp.setdescription(q.value(7).toByteArray().data());
		temp.setDeposit(q.value(8).toULongLong());
		//below to be realized;
		temp.setTotalConsume(9494595);
		temp.setConsumeTime(12);
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all customers. amount: ", r->size());
	return r;
}


Customer* CmDbThread::getCustomer(uint32 id){
	Customer* temp = NULL;
	if(0 == id || !openDb(DBNAME)){//id 0 customer surely not in the database
		return temp;
	}
	DBDEC("getting one customer:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
	QString query = QString(SELECT_CUSTOMER_BYID).arg(id);
	if(q.exec(query)){
		if(q.isActive()) {
			temp->setid(q.value(0).toUInt());
			temp->setpassword(q.value(1).toByteArray().data());
			temp->setname(q.value(1).toByteArray().data());
			temp->setsex(q.value(2).toUInt());
			temp->setLevel(q.value(3).toUInt());
			temp->setcell(q.value(4).toByteArray().data());
			temp->setphone(q.value(5).toByteArray().data());
			temp->setaddress(q.value(6).toByteArray().data());
			temp->setdescription(q.value(7).toByteArray().data());
			temp->setDeposit(q.value(8).toULongLong());
			//below to be realized;
			temp->setTotalConsume(9494595);
			temp->setConsumeTime(12);
		}
	}
	closeDb();
	DBHEX("get one customer completed:", temp->name());
	return temp;
}


list<CustomerLevel>* CmDbThread::getCustomerLevels(){
	list<CustomerLevel>* r = new list<CustomerLevel>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}
	DBHEX("getting all customer levels", "...");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
	q.exec(SELECT_CUSTOMERLEVEL_ALL);
	CustomerLevel temp;

	while (q.next()) {
		temp.setId(q.value(0).toUInt());
		temp.setName(q.value(1).toByteArray().data());
		temp.setTotalCosume(q.value(2).toULongLong());
		temp.setDiscount(q.value(2).toUInt());
		temp.setDescription(q.value(3).toByteArray().data());
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all customer levels completed. amount:", r->size());
	return r;
}


QByteArray* CmDbThread::getImage(uint32 id){
	QByteArray* image = new QByteArray;
	image->clear();

	if(0 == id || !openDb(DBNAME)) {//id 0 customer surely not in the database
		return image;
	}

	DBDEC("getting customer image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
/*
	QString check = QString(CHECK_CUSTOMERIMAGE_BYID).arg(id);
	if(q.exec(check)) {
		if(!q.isActive()) return image;
	}
*/
	QString get = QString(GET_CUSTOMERIMAGE_BYID).arg(id);
	if(q.exec(get)) {
		if(q.isActive()) {
			if(NULL != q.value(0).toByteArray().data())
				*image = q.value(0).toByteArray();
		}
	}

	closeDb();
	DBHEX("get customer image completed.", "");
	return image;
}


bool CmDbThread::modifyCustomer(Customer* data){
	bool r =false;
	if(0 == data->id() || !openDb(DBNAME)) {//id 0 customer surely not in the database
		return r;
	}

	DBHEX("modifying customer...", data->name());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));

	QString check = QString(CHECK_CUSTOMER_BYID).arg(data->id());
	q.exec(check);
	if(q.isActive()) {
		QString modifstr = QString(UPDATA_CUSTOMER_BYID)
			.arg(data->password().c_str()).arg(data->name().c_str())
			.arg(data->sex()).arg(data->getLevel()).arg(data->cell().c_str())
			.arg(data->phone().c_str()).arg(data->address().c_str())
			.arg(data->description().c_str()).arg(data->getDeposit())
			.arg(data->id()); 
		r = q.exec(modifstr);
	}
	closeDb();
	DBDEC("modify customer complete", r);
	return r;
}

bool CmDbThread::modifyCustomerLevel(CustomerLevel* data){
	bool r = false;
	if(!openDb(DBNAME)) {
		return r;
	}
	
	DBHEX("modifying customer type ...", data->getName());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
	QString check = QString(SELECT_CUSTOMERLEVEL_BYID).arg(data->getId());
	q.exec(check);
	if (q.isActive()) {
		QString update = QString(UPDATA_CUSTOMERLEVEL)
			.arg(data->getName().c_str()).arg(data->getTotalCosume())
			.arg(data->getDiscount()).arg(data->getDescription().c_str())
			.arg(data->getId());
		r = q.exec(update);
	}

	closeDb();
	DBDEC("modify customer levels completed", r);
	return r;
}


bool CmDbThread::removeCustomer(uint32 id){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBDEC("removing customer...", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));
	QString remove = QString(DELETE_CUSTOMER_BYID).arg(id);
	r = q.exec(remove);
	if(r) {
		removeImage(id);
	}
	closeDb();
	DBDEC("remove customer complete", r);
	return r;
}


bool CmDbThread::removeCustomerLevel(uint32 id){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBHEX("removing customer level...", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));

	QString check = QString(CHECK_CUSTOMERLEVEL_BYID).arg(id);
	q.exec(check);
	if(!q.isActive()) {//this customer level is not inuse. remove!
		QString remove = QString(DELETE_CUSTOMERLEVEL_BYID).arg(id);
		r = q.exec(remove);
	}
	closeDb();
	DBDEC("remove customer level complete", r);
	return r;
}


bool CmDbThread::removeImage(uint32 id){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}

	DBDEC("delete customer image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_CM));

	r= q.exec(QString(DELETE_CUSTOMERIMAGE).arg(id));
	DBDEC("delete customer image completed:", r);
	return r;
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