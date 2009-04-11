#include "ThreadDatabase.h"
#include "common.h"
#include "messagedef.h"
#include "Message.h"
#include <QCoreApplication>
#include "TEvent.h"
#include "Staff.h"

ThreadDatabase::ThreadDatabase(QObject *parent)
:QThread(parent)
{
	m_tempMsg = NULL;
	db = QSqlDatabase::addDatabase("QSQLITE");
	#ifdef D_DEMO
	stuffList.clear();
	Staff temp;
	temp.SetID("1");
	temp.SetSex(SEX_MALE);
	temp.SetDescrp("SeaShore£¨Ë¼Ë÷£©Èí¼þ");
	temp.SetName("¹ùêØ");
	temp.SetType(TYPE_SUPPER);
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BOSS);
	temp.SetID("2");
	temp.SetName("ÁõÊ¢");
	temp.SetLevel(LEVEL_ADVANCED);
	stuffList.push_back(temp);	
	temp.SetType(TYPE_SHOP_MANAGER);
	temp.SetID("3");
	temp.SetName("Ò¶Ï×ÃÏ");
	temp.SetLevel(LEVEL_SKILLED);
	stuffList.push_back(temp);	
	temp.SetType(TYPE_CASHER);
	temp.SetID("4");
	temp.SetName("½­ÔóÃû");
	temp.SetLevel(LEVEL_EXPERIENCED);
	temp.SetSex(SEX_FEMALE);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BARBER);
	temp.SetID("5");
	temp.SetName("ºú½ðÌÎ");
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BEAUTICIAN);
	temp.SetID("6");
	temp.SetName("Ï°½ðÆ¿");
	temp.SetSex(SEX_UNDEFINED);
	temp.SetLevel(LEVEL_ROOKIE);
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
				int id = atoi(static_cast<Staff*>(Action.data())->ID().c_str());
				if(id >= 1 && id <= 6  ) {
					m_tempMsg = new Message(EVENT_LOGGEDIN, (void*)(&(stuffList[id-1])));
					QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
					QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				}
				break;
			}
			case ACTION_GETSTAFF:
			{
				m_tempMsg = new Message(EVENT_STAFFS, (void*)(&stuffList));
				QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				break;
			}
			case ACTION_LOGOFF:
			{
				Action.setType(EVENT_LOGGEDOFF);
				break;
			}
			default:
				break;	
		}
		
//		delete m_tempMsg;
//		m_tempMsg = NULL;
	}
}

void ThreadDatabase::QueueAction(Message& Action)
{
	if(!isRunning()) {
		start(HighPriority);
	}

	mutex.lock();
	m_listActionBuffer.push_back(Action);
	mutex.unlock();


	mutex.lock();
	if(!m_listActionBuffer.empty())
		bufferEmpty.wakeOne();
	mutex.unlock();

}
