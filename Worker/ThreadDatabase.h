#ifndef ThreadDatabase_h
#define ThreadDatabase_h

#include "common.h"
#include "worker_global.h"
#include "Message.h"
#ifdef D_DEMO
#include "Stuff.h"
#endif
#include "QThread.h"
#include <QMutex>
#include <QWaitCondition>
#include <list>
using namespace std;

class WORKER_EXPORT ThreadDatabase : public QThread
{

	Q_OBJECT
public:
	ThreadDatabase(QObject *parent = 0);
	~ThreadDatabase();
	void QueueAction(Message& action);

protected:
	void run();

signals:
	void hasEvent(Message & ev);

protected:
	QMutex mutex;
    QWaitCondition bufferEmpty;
	list<Message> m_listActionBuffer;

 private:
#ifdef D_DEMO
	list<Stuff> stuffList;
#endif

};

#endif