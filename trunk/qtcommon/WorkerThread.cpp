#include "WorkerThread.h"
#include <QCoreApplication>
#include "TEvent.h"
#include "Message.h"
#include "messagedef.h"

WorkerThread::WorkerThread(QObject *parent, QThread::Priority priority)
:QThread(parent)
{
	m_priority = priority;
	m_tempMsg = NULL;
}

WorkerThread::~WorkerThread()
{
	if(NULL != m_tempMsg)
		delete m_tempMsg;
}

void WorkerThread::QueueAction(Message& Action)
{
	if(!isRunning()) {
		start(m_priority);
	}

	mutex.lock();
	m_listActionBuffer.push_back(Action);
	mutex.unlock();


	mutex.lock();
	if(!m_listActionBuffer.empty())
		bufferEmpty.wakeOne();
	mutex.unlock();
}

void WorkerThread::run() {
	DBINFO("worker thread start @", this);
	for(;;) {
		mutex.lock();
		if(m_listActionBuffer.empty())
			bufferEmpty.wait(&mutex);
		mutex.unlock();

		mutex.lock();
		Message Action = m_listActionBuffer.front();
		m_listActionBuffer.pop_front();
		mutex.unlock();

		WorkerThreadMain(Action);
	}
}

void WorkerThread::postEvent(Message* ev, uint32 type)
{
	DBINFO("posting event...", "");
	QEvent* qev= new TEvent((QEvent::Type)type, ev);
	QCoreApplication::postEvent(parent(), qev,Qt::HighEventPriority);
	DBINFO("posted event to: ", parent());
}

