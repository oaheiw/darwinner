///////////////////////////////////////////////////////////
//  DUIObserver.h
//  Implementation of the Class DUIObserver
//  Created on:      07-ËÄÔÂ-2009 16:59:42
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_83F8E378_5998_48c9_9510_20344DB3D52D__INCLUDED_)
#define EA_83F8E378_5998_48c9_9510_20344DB3D52D__INCLUDED_

#include "DUIHandler.h"

class DUIObserver
{

public:
	DUIObserver();
	virtual ~DUIObserver();

	virtual void OnEvent(Message& ev);
	void SetHandler(DUIHandler* handler);

private:
	DUIHandler m_uiHandler;

};
#endif // !defined(EA_83F8E378_5998_48c9_9510_20344DB3D52D__INCLUDED_)
