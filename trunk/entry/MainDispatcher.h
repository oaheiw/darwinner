///////////////////////////////////////////////////////////
//  MainDispatcher.h
//  Implementation of the Class MainDispatcher
//  Created on:      02-ËÄÔÂ-2009 18:03:22
//  Original author: Sunlight Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_AC4D55BE_D1FE_4dc3_80A8_DB54062F56FB__INCLUDED_)
#define EA_AC4D55BE_D1FE_4dc3_80A8_DB54062F56FB__INCLUDED_

#include "IEventObserver.h"
#include "IActionHandler.h"
#include <string>
using namespace std;
class entry;
class DarwinMain;
//#include "Singleton.h"

class MainDispatcher : public IEventObserver
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
//	static MainDispatcher* instance();

//protected:


private:
//	static MainDispatcher* m_instance;
//	IActionHandler *m_IActionHandler;
	entry* m_entryWindow;
	DarwinMain* m_mainWindow;

};
#endif // !defined(EA_AC4D55BE_D1FE_4dc3_80A8_DB54062F56FB__INCLUDED_)
