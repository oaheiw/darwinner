#include "ThreadDatabase.h"
#include "common.h"
#include "messagedef.h"
#include "Message.h"
#include <QCoreApplication>
#include "TEvent.h"
#include "Staff.h"
 #include <QSqlQuery>
#include <QVariant>
#include "dbquery.h"

ThreadDatabase::ThreadDatabase(QObject *parent)
:QThread(parent)
{
	m_tempMsg = NULL;
	db = QSqlDatabase::addDatabase("QSQLITE");
	#ifdef D_DEMO
	stuffList.clear();
	Staff temp;
	temp.SetID(1);
	temp.SetSex(SEX_MALE);
	temp.SetDescrp("SeaShore£¨Ë¼Ë÷£©Èí¼þ");
	temp.SetName("¹ùêØ");
	temp.SetType(TYPE_SUPPER);
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BOSS);
	temp.SetID(2);
	temp.SetName("ÁõÊ¢");
	temp.SetLevel(LEVEL_ADVANCED);
	stuffList.push_back(temp);	
	temp.SetType(TYPE_SHOP_MANAGER);
	temp.SetID(3);
	temp.SetName("Ò¶Ï×ÃÏ");
	temp.SetLevel(LEVEL_SKILLED);
	stuffList.push_back(temp);	
	temp.SetType(TYPE_CASHER);
	temp.SetID(4);
	temp.SetName("½­ÔóÃû");
	temp.SetLevel(LEVEL_EXPERIENCED);
	temp.SetSex(SEX_FEMALE);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BARBER);
	temp.SetID(5);
	temp.SetName("ºú½ðÌÎ");
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BEAUTICIAN);
	temp.SetID(6);
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
			case ACTION_INIT:
			{
				m_tempMsg = new Message(EVENT_INIT);
				QEvent* ev1 = new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev1,Qt::HighEventPriority);
				initDb();
				m_tempMsg = new Message(EVENT_SYSTEM_START);
				QEvent* ev2 = new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev2,Qt::HighEventPriority);
				break;
			}
			case ACTION_LOGIN:
			{
				Staff* staff = static_cast<Staff*>(Action.data());
				int id = staff->ID();
				if(id >= 1 && id <= 6  ) {
					m_tempMsg = new Message(EVENT_LOGGEDIN, (void*)(&(stuffList[id-1])));
					QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
					QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				}
				delete staff;
				break;
			}
			case ACTION_GETSTAFF:
			{
				db.setDatabaseName(DBNAME);
				bool re =db.open();
				QSqlQuery q = QSqlQuery(db);
				q.exec(SELECT_STAFF_NOIMAGE);
				Staff temp;
				vector<Staff>* r = new vector<Staff>;
				while (q.next()) {
					temp.SetID(q.value(0).toUInt());
					temp.SetPassword(q.value(1).toByteArray().data());
					temp.SetName(q.value(2).toByteArray().data());
					temp.SetType(q.value(3).toUInt());
					temp.SetLevel(q.value(4).toUInt());
					temp.SetSex((byte)(q.value(5).toUInt()));
					//temp.SetStatus(q.value(6).toChar().toAscii());
					temp.SetCell(q.value(7).toByteArray().data());
					temp.SetPhone(q.value(8).toByteArray().data());
					temp.SetAddress(q.value(9).toByteArray().data());
					temp.SetDescrp(q.value(10).toByteArray().data());
					r->push_back(temp);
				}
				db.close();

				m_tempMsg = new Message(EVENT_STAFFS, (void*)(r));
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


bool ThreadDatabase::initDb()
{
	db.setDatabaseName(DBNAME);
	if(!db.open()) {
		return false;
	}
	QSqlQuery q = QSqlQuery(db);
	q.exec(CREATE_STAFF_TABLE);
	q.exec(CREATE_JOB_TABLE);
	q.exec(CREATE_LEVET_TABLE);
	q.exec(CREATE_ORDERS_TABLE);
	q.exec(CREATE_GOODS_TABLE);
//	q.exec(CREATE_);
	

	
	q.prepare(INSERTINTO_STAFF);
	vector<Staff>::iterator it = stuffList.begin();
	while(it != stuffList.end()) {
		q.bindValue(":password", it->Password().c_str());
		q.bindValue(":name", it->Name().c_str());
		q.bindValue(":jobId", it->Type());
		q.bindValue(":levelId", it->Level());
		q.bindValue(":sex", it->Sex());
		q.bindValue(":status", '1');
		q.bindValue(":cell", it->cell().c_str());
		q.bindValue(":phone", it->phone().c_str());
		q.bindValue(":address", it->address().c_str());
		q.bindValue(":descrption", it->Descrp().c_str());
		q.bindValue(":image", "");
		q.exec();
		it++;
	}
	db.close();
	return true;
}
