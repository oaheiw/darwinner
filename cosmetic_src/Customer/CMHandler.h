///////////////////////////////////////////////////////////
//  CMHandler.h
//  Implementation of the Class CMHandler
//  Created on:      24-ÎåÔÂ-2009 16:59:43
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_7514165D_EE77_4d55_B45B_55236C586088__INCLUDED_)
#define EA_7514165D_EE77_4d55_B45B_55236C586088__INCLUDED_

#include "IEventObserver.h"
#include "DUIHandler.h"
class Message;
class DUIObserver;
#include "Customer.h"
#include "CustomerLevel.h"

#include <list>
using namespace std;

class CMHandler : public IEventObserver, public DUIHandler
{
public:
	CMHandler();
	virtual ~CMHandler();
	void OnEvent(Message& ev);
	void StartAction(Message& act);

private:
	list<Customer> m_customerCache;
	list<CustomerLevel> m_customerLevelCache;
	DUIObserver* m_mainWindow;
};
#endif // !defined(EA_7514165D_EE77_4d55_B45B_55236C586088__INCLUDED_)
