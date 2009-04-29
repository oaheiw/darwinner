#ifndef BMHANDLER_H
#define BMHANDLER_H

#include "DUIHandler.h"
#include "IEventObserver.h"

#include <list>
#include <map>
#include <string>
class Message;

using namespace std;

class BMHandler  : public DUIHandler, public IEventObserver
{
public:
	BMHandler();
	~BMHandler();
	void StartAction(Message& act);
	void OnEvent(Message & ev);

private:
	DUIObserver* m_mainWindow;
};

#endif // BMHANDLER_H
