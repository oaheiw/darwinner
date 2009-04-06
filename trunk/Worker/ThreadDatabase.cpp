#include "ThreadDatabase.h"
#include "common.h"
#include "Message.h"
#include <QCoreApplication>
#include "TEvent.h"
#include "Stuff.h"

ThreadDatabase::ThreadDatabase(QObject *parent)
:QThread(parent)
{
	m_tempMsg = NULL;
	#ifdef D_DEMO
	stuffList.clear();
	Stuff temp;
	temp.SetID("111");
	temp.SetPassword("111");
	temp.SetDescrp("¹þ¹þ¹þ¹þ");
	temp.SetName("¹ùêØ");
	temp.SetType(TYPE_BOSS);
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BEAUTICIAN);
	temp.SetID("222");
	temp.SetName("ÁõÊ¢");
	stuffList.push_back(temp);	
	temp.SetType(TYPE_BEAUTICIAN);
	temp.SetID("333");
	temp.SetName("Ò¶Ï×ÃÏ");
	stuffList.push_back(temp);
#endif
}

ThreadDatabase::~ThreadDatabase()
{
	if(NULL != m_tempMsg)
		delete m_tempMsg;
}

void ThreadDatabase::run() {
	for(;;) {
		mutex.lock();
		if(m_listActionBuffer.empty())
			bufferEmpty.wait(&mutex);
		mutex.unlock();

		mutex.lock();
		Message Action = m_listActionBuffer.front();
		m_listActionBuffer.pop_front();
		mutex.unlock();
		
		switch(Action.type()) {
			case ACTION_LOGIN:
			{
				if(static_cast<Stuff*>(Action.data())->ID() == "333") {
					m_tempMsg = new Message(EVENT_LOGGEDIN, (void*)(&(stuffList.back())));
					QEvent* ev = new TEvent(static_cast<QEvent::Type>(WorkerEventType::Db), m_tempMsg);
					QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				}
				break;
			}
			case ACTION_STUFFMGNT:
			{
				Action.setType(EVENT_STUFFMGNT);
				break;
			}
			case ACTION_LOGOFF:
			{
				Action.setType(EVENT_LOGGEDOFF);
				break;
			}
			case ACTION_EXIT:
			{
				Action.setType(EVENT_EXIT);
				break;
			}
			default:
				break;	
		}
	}
}

void ThreadDatabase::QueueAction(Message& Action)
{
	if(!isRunning()) {
		start(LowPriority);
	}

	mutex.lock();
	m_listActionBuffer.push_back(Action);
	mutex.unlock();


	mutex.lock();
	if(!m_listActionBuffer.empty())
		bufferEmpty.wakeOne();
	mutex.unlock();

}