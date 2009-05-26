///////////////////////////////////////////////////////////
//  CmDbThread.h
//  Implementation of the Class CmDbThread
//  Created on:      26-ÎåÔÂ-2009 16:48:51
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_6CFB78C3_8249_42c6_B08B_E55A4B8FD790__INCLUDED_)
#define EA_6CFB78C3_8249_42c6_B08B_E55A4B8FD790__INCLUDED_

#include "common.h"
#include "DbThread.h"
class Customer;
class CustomerLevel;

#include <list>
using namespace std;

class CmDbThread : public DbThread
{

public:
	CmDbThread(QObject *parent = 0, 
		QThread::Priority priority = QThread::NormalPriority);
	virtual ~CmDbThread();

protected:
	virtual void WorkerThreadMain(Message& action);

private:
	bool addCustomer(Customer* data);
	bool addCustomerLevel(CustomerLevel* data);
	bool addImage(uint32 id, QByteArray& data);
	list<Customer>* getAllCustomer();
	Customer* getCustomer(uint32 id);
	list<CustomerLevel>* getCustomerLevels();
	QByteArray* getImage(uint32 id);
	bool modifyCustomer(Customer* data);
	bool modifyCustomerLevel(CustomerLevel* data);
	bool removeCustomer(uint32 id);
	bool removeCustomerLevel(uint32 id);
	bool removeImage(uint32 id);

};
#endif // !defined(EA_6CFB78C3_8249_42c6_B08B_E55A4B8FD790__INCLUDED_)
