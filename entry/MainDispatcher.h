///////////////////////////////////////////////////////////
//  MainDispatcher.h
//  Implementation of the Class MainDispatcher
//  Created on:      02-Apr-2009 18:03:22
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_AC4D55BE_D1FE_4dc3_80A8_DB54062F56FB__INCLUDED_)
#define EA_AC4D55BE_D1FE_4dc3_80A8_DB54062F56FB__INCLUDED_

#include <string>
using namespace std;

#include "IEventObserver.h"
#include "DUIHandler.h"
class DUIObserver;

class MainDispatcher : public IEventObserver, public DUIHandler
{
public:
	MainDispatcher();
	virtual ~MainDispatcher();
	void Login(string& id, string& pw);
	void Logoff();
	void SelfService(string& id, string& pw);
	void OnEvent(Message& Msg);
	void Start();
	void StuffMgnt();
	void StartAction(Message & act);

private:
	DUIObserver* m_entryWindow;
	DUIObserver* m_mainWindow;

};
#endif // !defined(EA_AC4D55BE_D1FE_4dc3_80A8_DB54062F56FB__INCLUDED_)
