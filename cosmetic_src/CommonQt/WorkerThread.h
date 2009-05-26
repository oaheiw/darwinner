#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "common.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <list>
using namespace std;
class Message;
//class QEvent;

class WorkerThread  : public QThread
{
public:
	WorkerThread(QObject *parent = 0, 
		QThread::Priority priority = QThread::NormalPriority);
	~WorkerThread();
	void QueueAction(Message& action);

protected:
	void run();
	QMutex mutex;
	QWaitCondition bufferEmpty;
	list<Message> m_listActionBuffer;
	Message* m_tempMsg;
	virtual void WorkerThreadMain(Message& action) = 0;
	void postEvent(Message* ev, uint32 type);

private:
	QThread::Priority m_priority;
};

#endif // WORKERTHREAD_H
