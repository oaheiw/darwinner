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
