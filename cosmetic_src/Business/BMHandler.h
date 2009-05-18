#ifndef BMHANDLER_H
#define BMHANDLER_H

#include "DUIHandler.h"
#include "IEventObserver.h"
#include "Business.h"
#include "BusinessType.h"
#include <list>
class Message;

using namespace std;

class BMHandler : public DUIHandler, public IEventObserver
{
public:
	BMHandler();
	~BMHandler();
	void StartAction(Message& act);
	void OnEvent(Message & ev);

private:
	DUIObserver* m_mainWindow;
	list<Business> m_businessCache;
	list<BusinessType> m_businessTypeCache;
	void checkRights(Message* action);
};

#endif // BMHANDLER_H
