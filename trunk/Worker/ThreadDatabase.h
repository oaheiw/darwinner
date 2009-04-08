#ifndef ThreadDatabase_h
#define ThreadDatabase_h

#include "common.h"
#include "worker_global.h"

#ifdef D_DEMO
#include "Staff.h"
#endif
#include <QThread.>
#include <QMutex>
#include <QWaitCondition>
class Message;
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

protected:
	QMutex mutex;
    QWaitCondition bufferEmpty;
	list<Message> m_listActionBuffer;
	Message* m_tempMsg;

 private:
#ifdef D_DEMO
	list<Staff> stuffList;
#endif

};

#endif