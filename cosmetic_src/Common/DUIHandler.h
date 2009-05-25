///////////////////////////////////////////////////////////
//  DUIHandler.h
//  Implementation of the Class DUIHandler
//  Created on:      07-Apr-2009 5:06:43 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_D5E34F8A_68A8_4430_8A5B_EB004BC1B72D__INCLUDED_)
#define EA_D5E34F8A_68A8_4430_8A5B_EB004BC1B72D__INCLUDED_

#include "common.h"
#include <list>
using namespace std;

class Message;
class DUIObserver;

class DUIHandler
{

public:
	DUIHandler();
	~DUIHandler();

	void SetObserver(DUIObserver* observer);
	virtual void StartAction(Message& act) = 0;
	void DeregisterObserver(DUIObserver* observer);

protected:
	/*if your system has user rights. Re-implement this method
	the default implementation always returns true*/
	virtual bool CheckRight(uint32 actionId);
	void BroadcastEvent(Message& ev);

private:
	list<DUIObserver*> m_listUiObserver;

};
#endif // !defined(EA_D5E34F8A_68A8_4430_8A5B_EB004BC1B72D__INCLUDED_)
