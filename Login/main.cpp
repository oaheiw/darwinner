#include <QtGui/QApplication>
#include "Message.h"
#include "messagedef.h"
#include "Singleton.cpp"

#include "WorkerFactory.h"
#include "Staff.h"
#include <string>
//Logic Hanlders
#include "SSMainHandler.h"
#include "SMHandler.h"
#include "systeminfo.h"
 #include <QCleanlooksStyle>
#include <QPlastiqueStyle>

int main(int argc, char *argv[])
{
	QApplication* app = new QApplication(argc, argv);
	QCleanlooksStyle* style = new QCleanlooksStyle();
	app->setStyle(style);
//	systeminfo* info = new systeminfo();
//	info->getCPUID();		
	IActionHandler* worker = Singleton<WorkerFactory>::instance()->CreateWorker();
	IEventObserver* login = Singleton<SSMainHandler>::instance();
	IEventObserver* sm = Singleton<SMHandler>::instance();

	login->SetHandler(worker);
	sm->SetHandler(worker);
	worker->SetObserver(login);
	worker->SetObserver(sm);

	Message* StartUp = new Message(ACTION_SYSTEM_START);
	worker->StartAction(*StartUp);
	delete StartUp;
	
	app->exec();
	delete app;

	return 1;
}
