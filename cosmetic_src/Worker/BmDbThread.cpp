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
#include <QSqlQuery>
#include <QVariant>
#include "dbquery.h"

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
			m_tempMsg = new Message(EVENT_ADDBUSINESS);
			if(addBusiness(business)) {
				addedBusiness = getBusiness(business->id());
				m_tempMsg->setData(addedBusiness);
				if(NULL != addedBusiness && NULL != image && !image->isEmpty()) {
					if(addImage(addedBusiness->id(), *image))
						m_tempMsg->setData2(getImage(addedBusiness->id()));
				}
			}
			delete business;
			image->clear();
			delete image;
			break;
		}
		case ACTION_REMOVEBUSINESS:
		{
			uint32* id = static_cast<uint32*>(action.data());
			uint32* result = new uint32(*id);
			if(!removeBusiness(*id))
				*result = 0;
			m_tempMsg = new Message(EVENT_REMOVEBUSINESS, result);
			delete id;
			break;
		}
		case ACTOIN_MODIFYBUSINESS:
		{
			Business* toModify = static_cast<Business*>(action.data());
			QByteArray* image = static_cast<QByteArray*>(action.data2());
			Business* modified = NULL;
			m_tempMsg = new Message(EVENT_MODIFYBUSINESS);
			if(modifyBusiness(toModify)) {
				modified = getBusiness(toModify->id());
				m_tempMsg->setData(modified);
				if(NULL != image && !image->isEmpty() && toModify->id() != 0) {
					if(addImage(modified->id(), *image))
						m_tempMsg->setData2(getImage(modified->id()));
				}
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
				if(!removeBusinessType(it->getId()))
					result->push_back(*it);
				it++;
			}
			delete toRemove;
			m_tempMsg = new Message(EVENT_REMOVEBUSINESSTYPE, result);
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
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBHEX("adding business...", data->name());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));

	q.prepare(INSERTINTO_BUSINESS);

	q.bindValue(":name", data->name().c_str());
	q.bindValue(":typeId", data->type());
	q.bindValue(":brand", data->brand().c_str());
	q.bindValue(":specification", data->specification().c_str());
	q.bindValue(":price", data->price());
	q.bindValue(":cost", data->cost());
	q.bindValue(":discount", data->discount());
	q.bindValue(":adjustable", data->getAdjustable());
	q.bindValue(":dualDiscount", (uint32)(data->isDualDiscoutn()));
	q.bindValue(":stocks", data->stocks());
	q.bindValue(":sales", data->sales());
	q.bindValue(":buys", data->buys());
	q.bindValue(":description", data->description().c_str());
	r = q.exec();
	if(r) {
		q.exec(SELECT_MAX_BUSINESSID);
		if(q.next())
			data->setId(q.value(0).toUInt());
	}
	closeDb();
	DBDEC("add business completed:", data->id());
	return r;
}

bool BmDbThread::addBusinessType(BusinessType* data){	
	bool r = false;
	if(0 == data->getId()) {
		if(!openDb(DBNAME)) {
			return r;
		}
		DBHEX("adding business type ...", data->getName());
		QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));
		q.prepare(INSERTINTO_BUSINESSTYPE_TABLE);
		q.bindValue(":name", data->getName().c_str());
		q.bindValue(":cate", data->getCategory());
		q.bindValue(":description", data->getDescription().c_str());
		r = q.exec();
		DBDEC("add business type completed", r);
		closeDb();
	} else {
		r = modifyBusinessType(data);
	}
	return r;
}


bool BmDbThread::addImage(uint32 id, QByteArray& data){
	bool r = true;
	if(!openDb(DBNAME)) {
		return r;
	}

	DBDEC("setting business image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));

	QString check = QString(CHECK_BUSINESSIMAGE_BYID).arg(id);
	if(q.exec(check)) {
		if(q.next())
			r = q.exec(QString(DELETE_BUSINESSIMAGE).arg(id));
	}
	if(r) {
		q.prepare(INSERT_BUSINESSIMAGE);
		q.bindValue(":id", id);
		q.bindValue(":data", data, QSql::Binary | QSql::In);
		r = q.exec();
	}
	closeDb();
	DBDEC("set business image complete", r);
	return r;
}


Business* BmDbThread::getBusiness(uint32 id){
	Business* temp = NULL;
	if(0 == id || !openDb(DBNAME)){//id 0 business surely not in the database
		return temp;
	}
	DBDEC("getting one business:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));
	QString query = QString(SELECT_BUSINESS_BYID).arg(id);
	if(q.exec(query)){
		if(q.next()) {
			temp = new Business();
			temp->setId(q.value(0).toUInt());
			temp->setName(q.value(1).toByteArray().data());
			temp->setType(q.value(2).toUInt());
			temp->setBrand(q.value(3).toByteArray().data());
			temp->setSpecification(q.value(4).toByteArray().data());
			temp->setPrice(q.value(5).toUInt());
			temp->setCost(q.value(6).toUInt());
			temp->setDiscount(q.value(7).toUInt());
			temp->setAdjustable(q.value(8).toUInt());
			temp->setDualDiscoutn(q.value(9).toBool());
			temp->setStocks(q.value(10).toUInt());
			temp->setSales(q.value(11).toUInt());
			temp->setBuys(q.value(12).toUInt());
			temp->setDescription(q.value(13).toByteArray().data());
			temp->setRating(rand()%100);
			//rating to be relized;
		}
	}
	closeDb();
	DBHEX("get one business completed:", temp->name());
	return temp;
}


list<BusinessType>* BmDbThread::getBusinessTypes(){
	list<BusinessType>* r = new list<BusinessType>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}
	DBHEX("getting all business types", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));
	q.exec(SELECT_BUSINESSTYPE_ALL);
	BusinessType temp;

	while (q.next()) {
		temp.setId(q.value(0).toUInt());
		temp.setName(q.value(1).toByteArray().data());
		temp.setCategory(q.value(2).toUInt());
		temp.setDescription(q.value(3).toByteArray().data());
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all business types completed. amount:", r->size());
	return r;

}


QByteArray* BmDbThread::getImage(uint32 id){
	QByteArray* image = new QByteArray;
	image->clear();
	
	if(0 == id || !openDb(DBNAME)) {//id 0 business surely not in the database
		return image;
	}
	
	DBDEC("getting business image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));

	QString check = QString(CHECK_BUSINESSIMAGE_BYID).arg(id);
	if(q.exec(check)) {
		if(!q.next()) return image;
	}

	QString get = QString(GET_BUSINESSIMAGE_BYID).arg(id);
	if(q.exec(get)) {
		if(q.next()) {
			if(NULL != q.value(0).toByteArray().data())
				*image = q.value(0).toByteArray();
		}
	}
	q.clear();
	closeDb();
	DBHEX("get business image completed.", "");
	return image;
}


bool BmDbThread::modifyBusiness(Business* data){
	bool r =false;
	if(0 == data->id() || !openDb(DBNAME)) {//id 0 business surely not in the database
		return r;
	}
	
	DBHEX("modifying business...", data->name());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));

	QString check = QString(CHECK_BUSINESS_BYID).arg(data->id());
	q.exec(check);
	if(!q.isActive()) return r;

	QString modifstr = QString(UPDATA_BUSINESS_BYID).arg(data->name().c_str())
		.arg(data->type()).arg(data->brand().c_str()).arg(data->specification().c_str())
		.arg(data->price()).arg(data->cost()).arg(data->discount()).arg(data->stocks())
		.arg(data->sales()).arg(data->buys()).arg(data->description().c_str())
		.arg(data->getAdjustable()).arg(data->isDualDiscoutn()).arg(data->id()); 
	r = q.exec(modifstr);
	closeDb();
	
	DBDEC("modify business complete", r);
	return r;
}


bool BmDbThread::modifyBusinessType(BusinessType* data){
	bool r = false;
	if(!openDb(DBNAME)) {
		return r;
	}
	
	DBHEX("modifying business type ...", data->getName());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));
	QString qstring = QString(SELECT_BUSINESSTYPE_BYID).arg(data->getId());
	q.exec(qstring);
	if (q.isActive()) 
	{
		QString update = QString(UPDATA_BUSINESSTYPE)
			.arg(data->getName().c_str()).arg(data->getCategory())
			.arg(data->getDescription().c_str()).arg(data->getId());
		r = q.exec(update);
	}

	closeDb();
	DBDEC("modify business type completed", r);
	return r;
}


bool BmDbThread::removeBusiness(uint32 id){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBDEC("removing business...", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));
	QString remove = QString(DELETE_BUSINESS_BYID).arg(id);
	r = q.exec(remove);
	if(r) {
		removeImage(id);
	}
	closeDb();
	DBDEC("remove business complete", r);
	return r;
}


bool BmDbThread::removeBusinessType(uint32 id){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBHEX("removing business type...", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));

	QString check = QString(CHECK_BUSINESSTYPE_BYID).arg(id);
	q.exec(check);
	if(!q.isActive()) {//this business type is not inuse. remove!
		QString remove = QString(DELETE_BUSINESSTYPE_BYID).arg(id);
		r = q.exec(remove);
	}
	closeDb();
	DBDEC("remove business type complete", r);
	return r;
}


bool BmDbThread::removeImage(uint32 id){
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}

	DBDEC("delete business image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));

	r= q.exec(QString(DELETE_BUSINESSIMAGE).arg(id));
	DBDEC("delete business image completed:", r);
	return r;
}



list<Business>* BmDbThread::getAllBusiness(){
	list<Business>* r = new list<Business>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}

	DBHEX("geting all business...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_BM));
	q.exec(SELECT_BUSINESS_ALL);
	Business temp;

	while (q.next()) {
		temp.setId(q.value(0).toUInt());
		temp.setName(q.value(1).toByteArray().data());
		temp.setType(q.value(2).toUInt());
		temp.setBrand(q.value(3).toByteArray().data());
		temp.setSpecification(q.value(4).toByteArray().data());
		temp.setPrice(q.value(5).toUInt());
		temp.setCost(q.value(6).toUInt());
		temp.setDiscount(q.value(7).toUInt());
		temp.setAdjustable(q.value(8).toUInt());
		temp.setDualDiscoutn(q.value(9).toBool());
		temp.setStocks(q.value(10).toUInt());
		temp.setSales(q.value(11).toUInt());
		temp.setBuys(q.value(12).toUInt());
		temp.setDescription(q.value(13).toByteArray().data());
		temp.setRating(rand()%100);
		//rating to be relized;
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all business. amount: ", r->size());
	return r;
}
