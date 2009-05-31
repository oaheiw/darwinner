#include <QtGui/QApplication>
#include <QCoreApplication>

#include "Message.h"
#include "messagedef.h"
#include "Singleton.h"
#include "AppParameter.h"

#include "WorkerFactory.h"
#include <QStyleFactory>
#include <QStyle>

//Logic Handlers
#include "SSMainHandler.h"
#include "SMHandler.h"
#include "BMHandler.h"
#include "CMHandler.h"
#include "systeminfo.h"

#ifdef _STATIC_RELEASE
#include <QtPlugin>
Q_IMPORT_PLUGIN(qico);
Q_IMPORT_PLUGIN(qjpeg);
Q_IMPORT_PLUGIN(qgif);
#endif

int main(int argc, char *argv[])
{	
	IActionHandler* worker = 
		Singleton<WorkerFactory>::instance()->CreateWorker();
	IEventObserver* login = Singleton<SSMainHandler>::instance();
	IEventObserver* sm = Singleton<SMHandler>::instance();
	IEventObserver* bm = Singleton<BMHandler>::instance();
	IEventObserver* cm = Singleton<CMHandler>::instance();
	
	worker->SetObserver(login);
	worker->SetObserver(sm);
	worker->SetObserver(bm);
	worker->SetObserver(cm);
	login->SetHandler(worker);
	sm->SetHandler(worker);
	bm->SetHandler(worker);
	cm->SetHandler(worker);

	QApplication* app = new QApplication(argc, argv);
	
	QStyle* style = QStyleFactory::
		create(Singleton<AppParameter>::instance()->getAppStyle().c_str());
	app->setStyle(style);
	app->setPalette(style->standardPalette());

	Message* StartUp = new Message(ACTION_SYSTEM_START);
	worker->StartAction(*StartUp);
	delete StartUp;
	
	app->exec();
	delete app;

	return 0;
}

