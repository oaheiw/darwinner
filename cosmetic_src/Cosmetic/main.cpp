#include <QtGui/QApplication>
#include <QCoreApplication>

#include "Message.h"
#include "messagedef.h"
#include "Singleton.cpp"

#include "WorkerFactory.h"
#include "Staff.h"
#include <string>
#include <QCleanlooksStyle>

//Logic Hanlders
#include "SSMainHandler.h"
#include "SMHandler.h"
#include "systeminfo.h"

#ifdef _STATIC_RELEASE
#include <QtPlugin>
Q_IMPORT_PLUGIN(qico);
Q_IMPORT_PLUGIN(qjpeg);
Q_IMPORT_PLUGIN(qgif);
#endif

#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))

int main(int argc, char *argv[])
{
	IActionHandler* worker = Singleton<WorkerFactory>::instance()->CreateWorker();
	IEventObserver* login = Singleton<SSMainHandler>::instance();
	IEventObserver* sm = Singleton<SMHandler>::instance();
	
	worker->SetObserver(login);
	worker->SetObserver(sm);
	login->SetHandler(worker);
	sm->SetHandler(worker);

	QApplication* app = new QApplication(argc, argv);
	QCleanlooksStyle* style = new QCleanlooksStyle();
	app->setStyle(style);

	Message* StartUp = new Message(ACTION_SYSTEM_START);
	worker->StartAction(*StartUp);
	delete StartUp;
	
	app->exec();
	delete app;

	return 1;
}
