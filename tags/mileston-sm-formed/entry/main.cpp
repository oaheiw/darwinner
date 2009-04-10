#include <QtGui/QApplication>
#include "Message.h"
#include "messagedef.h"
#include "Singleton.cpp"

#include "WorkerFactory.h"

//Logic Hanlders
#include "MainDispatcher.h"
#include "SMHandler.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	IActionHandler* worker = Singleton<WorkerFactory>::instance()->CreateWorker();
	MainDispatcher* login = Singleton<MainDispatcher>::instance();
	IEventObserver* sm = Singleton<SMHandler>::instance();
	
	login->SetHandler(worker);
	sm->SetHandler(worker);
	worker->SetObserver(login);
	worker->SetObserver(sm);

	Message* StartUp = new Message(ACTION_SYSTEM_START);
	worker->StartAction(*StartUp);
	delete StartUp;
	
	return a.exec();
}
