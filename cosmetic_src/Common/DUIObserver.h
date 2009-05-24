///////////////////////////////////////////////////////////
//  DUIObserver.h
//  Implementation of the Class DUIObserver
//  Created on:      07-Apr-2009 5:06:43 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_3C747DAE_7CEE_409c_B90E_4E51C6EBAC51__INCLUDED_)
#define EA_3C747DAE_7CEE_409c_B90E_4E51C6EBAC51__INCLUDED_

class DUIHandler;
class Message;

class DUIObserver
{

public:
	DUIObserver();
	~DUIObserver();

	virtual void OnEvent(Message& ev) = 0;
	void SetHandler(DUIHandler* handler);
	DUIHandler* GetHandler();

private:
	DUIHandler* m_uiHandler;

};
#endif // !defined(EA_3C747DAE_7CEE_409c_B90E_4E51C6EBAC51__INCLUDED_)
