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
	IActionHandler* worker = Singleton<WorkerFactory>::instance()->CreateWorker();
	DBINFO("worker created!");
	IEventObserver* login = Singleton<SSMainHandler>::instance();
	DBINFO("login created!");
	IEventObserver* sm = Singleton<SMHandler>::instance();
	DBINFO("sm created!");
	
	worker->SetObserver(login);
	worker->SetObserver(sm);
	login->SetHandler(worker);
	sm->SetHandler(worker);

	QApplication* app = new QApplication(argc, argv);
	DBINFO("app newed!");
	QCleanlooksStyle* style = new QCleanlooksStyle();
	app->setStyle(style);
	DBINFO("style changed!");

	Message* StartUp = new Message(ACTION_SYSTEM_START);
	worker->StartAction(*StartUp);
	delete StartUp;
	
	app->exec();
	delete app;

	return 1;
}
