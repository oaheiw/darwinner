///////////////////////////////////////////////////////////
//  SMHandler.h
//  Implementation of the Class SMHandler
//  Created on:      08-Apr-2009 14:40:22 PM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_E00DDA3D_9ED8_47b4_8128_B3398B0D9178__INCLUDED_)
#define EA_E00DDA3D_9ED8_47b4_8128_B3398B0D9178__INCLUDED_
#include "staffmanagement_global.h"
#include "DUIHandler.h"
#include "IEventObserver.h"
#include "Staff.h"
#include <list>
#include <map>
#include <string>
using namespace std;

class DLL_EXPORT SMHandler : public DUIHandler, public IEventObserver
{

public:
	SMHandler();
	virtual ~SMHandler();

	void Start();
	void StartAction(Message& act);
	void OnEvent(Message & ev);

private:
	list<Staff> m_staffCache;
	map<uint32, string> m_staffLevel;
	map<uint32, string> m_staffType;
	map<uint32, string> m_taskState;
	map<uint32, string> m_taskType;
	DUIObserver* m_mainWindow;
};
#endif // !defined(EA_E00DDA3D_9ED8_47b4_8128_B3398B0D9178__INCLUDED_)
