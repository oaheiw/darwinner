///////////////////////////////////////////////////////////
//  DUIHandler.h
//  Implementation of the Class DUIHandler
//  Created on:      07-ËÄÔÂ-2009 16:59:38
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_88D0FA99_BDAF_4c41_95F4_B315A47F585F__INCLUDED_)
#define EA_88D0FA99_BDAF_4c41_95F4_B315A47F585F__INCLUDED_

class DUIHandler
{

public:
	DUIHandler();
	virtual ~DUIHandler();

	void SetObserver()(DUIObserver* observer);
	virtual void startAction(Message& act);

protected:
	DUIObserver m_uiObserver;

};
#endif // !defined(EA_88D0FA99_BDAF_4c41_95F4_B315A47F585F__INCLUDED_)
