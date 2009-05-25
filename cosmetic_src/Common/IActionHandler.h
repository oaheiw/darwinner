///////////////////////////////////////////////////////////
//  IActionHandler.h
//  Implementation of the Class IActionHandler
//  Created on:      02-Apr-2009 18:09:50
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_CCBDEB35_298E_4ed5_8E93_249838D0E10A__INCLUDED_)
#define EA_CCBDEB35_298E_4ed5_8E93_249838D0E10A__INCLUDED_

#include "common.h"
#include <list>
class Message; 
class IEventObserver;
using namespace std;

class IActionHandler
{

public:
	IActionHandler() { }
	~IActionHandler() { }
	virtual void StartAction(Message& Action) =0;
	void SetObserver(IEventObserver* observer);
	void DeregisterObserver(IEventObserver* observer);


protected:
	void BroadcastEvent(Message& ev);

private:
	list<IEventObserver*> m_listObserver;

};
#endif // !defined(EA_CCBDEB35_298E_4ed5_8E93_249838D0E10A__INCLUDED_)
