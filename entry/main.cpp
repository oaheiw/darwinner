#include <QtGui/QApplication>
#include "Singleton.cpp"
#include "MainDispatcher.h"
#include "WorkerFactory.h"
#include "IActionHandler.h"
#include "Worker.h"
#include "Message.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IActionHandler* dataworker = Singleton<WorkerFactory>::instance()->CreateWorker();
	MainDispatcher* dispathcer = Singleton<MainDispatcher>::instance();
	dispathcer->SetHandler(dataworker);
	dataworker->SetObserver(dispathcer);
	dispathcer->Start();
	return a.exec();
}
