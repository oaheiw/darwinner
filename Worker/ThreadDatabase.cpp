#include "ThreadDatabase.h"
#include "common.h"
#include "Message.h"
#include <QCoreApplication>
#include "TEvent.h"
#include "Stuff.h"

ThreadDatabase::ThreadDatabase(QObject *parent)
:QThread(parent)
{
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

ThreadDatabase::~ThreadDatabase(void)
{
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
		
		Message uiEv;

		switch(Action.type()) {
			case ACTION_LOGIN:
			{
//				LOGIN para;
//				memcpy(&para, ev.data(), sizeof(LOGIN));

				if(static_cast<Stuff*>(Action.data())->ID() == "333") {
					/*
					STUFF para;
					ev.setType(EVENT_LOGGEDIN);
					memcpy(&para.descrp, stuffList.front().Descrp().c_str(), DESCRP_MAX_LEN);
					memcpy(&para.id, stuffList.front().ID().c_str(), ID_MAX_LEN);
					para.level = stuffList.front().Level();
					memcpy(&para.name, stuffList.front().Name().c_str(), STUFFNAME_MAX_LEN);
					para.type = stuffList.front().Type();
					memcpy(&para.pw, stuffList.front().Password().c_str(), PW_MAX_LEN);
					Action.setData((byte*)&para, sizeof(STUFF));
//					if (receivers(SIGNAL(hasEvent(Message&))) > 0) {
*/					uiEv.setType(EVENT_LOGGEDIN);
					uiEv.setData((void*)(&(stuffList.back())));
					TEvent* ev = new TEvent(static_cast<QEvent::Type>(WorkerEventType::Db));
						ev->setData(&uiEv);
						QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
//					}
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

void ThreadDatabase::QueueAction(Message& Action) {
//	QMutexLocker locker(&mutex);
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