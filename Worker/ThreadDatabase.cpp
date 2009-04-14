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
#include <iostream>

ThreadDatabase::ThreadDatabase(QObject *parent)
:QThread(parent)
{
	m_tempMsg = NULL;
	db = QSqlDatabase::addDatabase("QSQLITE");
/*
#ifdef D_DEMO
	stuffList.clear();
	Staff temp;
	temp.SetID(1);
	temp.SetSex(SEX_MALE);
	temp.SetDescrp("SeaShore（思索）软件");
	temp.SetName("郭曦");
	temp.SetType(TYPE_SUPPER);
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BOSS);
	temp.SetID(2);
	temp.SetName("刘盛");
	temp.SetLevel(LEVEL_ADVANCED);
	stuffList.push_back(temp);	
	temp.SetType(TYPE_SHOP_MANAGER);
	temp.SetID(3);
	temp.SetName("叶献孟");
	temp.SetLevel(LEVEL_SKILLED);
	stuffList.push_back(temp);	
	temp.SetType(TYPE_CASHER);
	temp.SetID(4);
	temp.SetName("江泽名");
	temp.SetLevel(LEVEL_EXPERIENCED);
	temp.SetSex(SEX_FEMALE);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BARBER);
	temp.SetID(5);
	temp.SetName("胡金涛");
	temp.SetLevel(LEVEL_MASTER);
	stuffList.push_back(temp);
	temp.SetType(TYPE_BEAUTICIAN);
	temp.SetID(6);
	temp.SetName("习金瓶");
	temp.SetSex(SEX_UNDEFINED);
	temp.SetLevel(LEVEL_ROOKIE);
	stuffList.push_back(temp);

#endif	*/
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
				Staff* staffIncome = static_cast<Staff*>(Action.data());
				Staff* staffDb = getStaff(staffIncome->ID());
				if(staffDb->ID() != 0 &&
					staffIncome->Password() == staffDb->Password() &&
					staffIncome->ID() == staffDb->ID()) {
					m_tempMsg = new Message(EVENT_LOGGEDIN, staffDb);
					QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
					QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				}
				delete staffIncome;
				break;
			}
			case ACTION_GEALLSTAFF:
			{
				db.setDatabaseName(DBNAME);
				bool re =db.open();
				QSqlQuery q = QSqlQuery(db);
				q.exec(SELECT_STAFF_NOIMAGE);
				Staff temp;
				list<Staff>* r = new list<Staff>;
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
				cout<<"get staffs"<<endl;
				m_tempMsg = new Message(EVENT_ALLSTAFF, (void*)(r));
				QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				break;
			}
			case ACTION_GETSTAFF:
			{
				uint32* id = static_cast<uint32*>(Action.data());
				m_tempMsg = new Message(EVENT_STAFF, getStaff(*id));
				QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
				delete id;
				break;
			}
			case ACTION_ADDSTAFF:
			{
				Staff* staff = static_cast<Staff*>(Action.data());
				addStaff(staff);
				delete staff;
				m_tempMsg = new Message(EVENT_STAFFADDED);
				QEvent* ev = new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
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
	cout<<"init db"<<endl;
	QSqlQuery q = QSqlQuery(db);
	q.exec(CREATE_STAFF_TABLE);
	
	DBINFO("creating super user...");
	q.prepare(INSERTINTO_STAFF);
	q.bindValue(":password", "111");
	q.bindValue(":name", "科思美管理员");
	q.bindValue(":jobId", 0);
	q.bindValue(":levelId", 4);
	q.bindValue(":sex", 0);
	q.bindValue(":status", '1');
	q.bindValue(":cell", "88888888");
	q.bindValue(":phone", "66666666");
	q.bindValue(":address", "中华人民共和国");
	q.bindValue(":descrption", "我是科思美系统超级管理员");
	q.bindValue(":image", "");
	q.exec();
	DBINFO("create super user complete!");

	q.exec(CREATE_JOB_TABLE);
	q.exec(CREATE_LEVET_TABLE);
	q.exec(CREATE_ORDERS_TABLE);
	q.exec(CREATE_GOODS_TABLE);
//	q.exec(CREATE_);
	
	db.close();
	return true;
}

Staff* ThreadDatabase::getStaff(uint32 id) 
{
	db.setDatabaseName(DBNAME);
	db.open();
	QSqlQuery q = QSqlQuery(db);
	QString query = QString("SELECT * FROM staff WHERE id = %1").arg(id);
	q.exec(query);
	Staff* temp = new Staff();
	if(q.next()) {
		temp->SetID(q.value(0).toUInt());
		temp->SetPassword(q.value(1).toByteArray().data());
		temp->SetName(q.value(2).toByteArray().data());
		temp->SetType(q.value(3).toUInt());
		temp->SetLevel(q.value(4).toUInt());
		temp->SetSex((byte)(q.value(5).toUInt()));
		//	temp->SetStatus((byte)(q.value(5).toUInt());
		temp->SetCell(q.value(7).toByteArray().data());
		temp->SetPhone(q.value(8).toByteArray().data());
		temp->SetAddress(q.value(9).toByteArray().data());
		temp->SetDescrp(q.value(10).toByteArray().data());
	}
	db.close();
	cout<<"get one staff completed"<<endl;
	return temp;
}
bool ThreadDatabase::addStaff(Staff* staff)
{
					db.setDatabaseName(DBNAME);
				if(!db.open()) {
					return false;
				}
				DBINFO("adding satff...");
				QSqlQuery q = QSqlQuery(db);

				q.prepare(INSERTINTO_STAFF);

				q.bindValue(":password", staff->Password().c_str());
				q.bindValue(":name", staff->Name().c_str());
				q.bindValue(":jobId", staff->Type());
				q.bindValue(":levelId", staff->Level());
				q.bindValue(":sex", staff->Sex());
				q.bindValue(":status", '1');
				q.bindValue(":cell", staff->cell().c_str());
				q.bindValue(":phone", staff->phone().c_str());
				q.bindValue(":address", staff->address().c_str());
				q.bindValue(":descrption", staff->Descrp().c_str());
				q.bindValue(":image", "");
				q.exec();
				db.close();
				DBINFO("add satff complete");
				return true;
}