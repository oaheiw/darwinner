///////////////////////////////////////////////////////////
//  BmDbThread.h
//  Implementation of the Class BmDbThread
//  Created on:      05-ÎåÔÂ-2009 11:40:31
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_6594F28D_DB37_4636_8095_CAF8A14A53D9__INCLUDED_)
#define EA_6594F28D_DB37_4636_8095_CAF8A14A53D9__INCLUDED_

#include "DbThread.h"
class Business;
class BusinessType;
class QByteArray;
class Message;
#include <list>
using namespace std;

class BmDbThread : public DbThread
{
public:
	BmDbThread(QObject *parent = 0, 
		QThread::Priority priority = QThread::NormalPriority);
	virtual ~BmDbThread();
	
protected:
	virtual void WorkerThreadMain(Message& action);

private:
	bool addBusiness(Business* data);
	bool addBusinessType(BusinessType* data);
	bool addImage(uint32 id, QByteArray& data);
	Business* getBusiness(uint32 id);
	list<BusinessType>* getBusinessTypes();
	QByteArray* getImage(uint32 id);
	bool modifyBusiness(Business* data);
	bool modifyBusinessType(BusinessType* data);
	bool removeBusiness(uint32 id);
	bool removeBusinessType(uint32 id);
	bool removeImage(uint32 id);
	list<Business>* getAllBusiness();

};
#endif // !defined(EA_6594F28D_DB37_4636_8095_CAF8A14A53D9__INCLUDED_)
