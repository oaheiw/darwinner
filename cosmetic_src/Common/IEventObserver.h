///////////////////////////////////////////////////////////
//  IEventObserver.h
//  Implementation of the Class IEventObserver
//  Created on:      02-Apr-2009 18:03:01
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_714FDA6F_77D3_4c14_91EA_D516282D9A93__INCLUDED_)
#define EA_714FDA6F_77D3_4c14_91EA_D516282D9A93__INCLUDED_

#include "common.h"
class Message; 
class IActionHandler;

class IEventObserver
{

public:
	IEventObserver(){

	}
	~IEventObserver(){

	}
	virtual void OnEvent(Message &) =0;
	void SetHandler(IActionHandler* handler);
protected:
	IActionHandler* m_handler;

};
#endif // !defined(EA_714FDA6F_77D3_4c14_91EA_D516282D9A93__INCLUDED_)
