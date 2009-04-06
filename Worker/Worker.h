///////////////////////////////////////////////////////////
//  Worker.h
//  Implementation of the Class Processer
//  Created on:      02-ËÄÔÂ-2009 18:10:13
//  Original author: Sunlight Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_20AED985_021D_47c7_AADB_219A004968B6__INCLUDED_)
#define EA_20AED985_021D_47c7_AADB_219A004968B6__INCLUDED_

#include "common.h"
#include "IActionHandler.h"
#include "IEventObserver.h"
#include <QObject>
#include "ThreadDatabase.h"
#include "worker_global.h"
class QEvent;

class WORKER_EXPORT Worker : public QObject, public IActionHandler
{
	Q_OBJECT
public:
	Worker(QObject *parent = 0);
	virtual ~Worker();
	virtual void StartAction(Message& Action) ;
	bool event ( QEvent * e );
 
 private:
	IEventObserver *m_IEventObserver;
	ThreadDatabase* m_databaseThread;

private slots:
	void IncomingEvent(Message& ev);
};
#endif // !defined(EA_20AED985_021D_47c7_AADB_219A004968B6__INCLUDED_)

