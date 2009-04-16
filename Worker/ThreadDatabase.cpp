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
#include <fstream>
#include <QSqlRecord>

ThreadDatabase::ThreadDatabase(QObject *parent)
:QThread(parent)
{
	m_tempMsg = NULL;
	db = QSqlDatabase::addDatabase("QSQLITE");
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
			case ACTION_SYSTEM_START:
			{
				if(checkDd()) {
					m_tempMsg = new Message(EVENT_SYSTEM_START);	
				}else{
					m_tempMsg = new Message(EVENT_WIZARD);
				}
				QEvent* ev= new TEvent((QEvent::Type)EventDb, m_tempMsg);
				QCoreApplication::postEvent(this->parent(), ev,Qt::HighEventPriority);
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
				DBINFO("get all staffs. amount: ", r->size())
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
			case ACTION_SETSUPERUSER:
			{
				Staff* staff = static_cast<Staff*>(Action.data());
				addSupperStaff(staff);
				delete staff;
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
	DBINFO("initializing database...", "");
	QSqlQuery q = QSqlQuery(db);
	q.exec(CREATE_STAFF_TABLE);
	q.exec(CREATE_JOB_TABLE);
	q.exec(CREATE_LEVET_TABLE);
	q.exec(CREATE_ORDERS_TABLE);
	q.exec(CREATE_GOODS_TABLE);
	q.exec(CREATE_SEX_TABLE);
	q.exec(CREATE_STATUS_TABLE);
	q.exec(CREATE_TASKS_TABLE);
	q.exec(CREATE_GOOSTYPE_TABLE);
	db.close();
	DBINFO("databese initialized.", "");
	return true;
}

bool ThreadDatabase::checkDd()
{
	bool re = false;
	bool exist;
	int length= 0;
	char* SQLiteMark;
	int isSQLite = -1;
	fstream testfile;
	testfile.open (DBFILE, fstream::in | fstream::out | fstream::app | fstream::binary);
	exist = testfile.is_open();
	if(exist) {
	  testfile.seekg (0, ios::end);
	  length = testfile.tellg();
	  testfile.seekg (0, ios::beg);

	  SQLiteMark = new char[SQLITEMARKLEN];
	  memset(SQLiteMark, 0, SQLITEMARKLEN);
	  testfile.read(SQLiteMark, SQLITEMARKLEN);
	  isSQLite = memcmp(SQLiteMark, SQLITEMARK, SQLITEMARKLEN);
	  testfile.close();
	}
	  
	if(!exist | 0 == length | 0 != isSQLite) {//first time running
		remove(DBFILE);
		m_tempMsg = new Message(EVENT_INIT);
		QEvent* ev1 = new TEvent((QEvent::Type)EventDb, m_tempMsg);
		QCoreApplication::postEvent(this->parent(), ev1,Qt::HighEventPriority);
		initDb();
		m_tempMsg = new Message(EVENT_INIT_FINISHED);
		QEvent* ev2 = new TEvent((QEvent::Type)EventDb, m_tempMsg);
		QCoreApplication::postEvent(this->parent(), ev2,Qt::HighEventPriority);
		re = false;
	} else {//database exists. check super user
		testfile.close();
		db.setDatabaseName(DBNAME);
		db.open();
		QSqlQuery q = QSqlQuery(db);
		QString query = QString("SELECT * FROM staff WHERE id = %1").arg(SUPERUSERID);
		q.exec(query);
		if(!q.next())
			re = false;
		else
			re = true;
		db.close();
	}
	return re;
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
	DBINFO("get one staff completed:", temp->Name())
	return temp;
}
bool ThreadDatabase::addStaff(Staff* staff)
{
	bool r =false;
	db.setDatabaseName(DBNAME);
	r = db.open();
	if(!r) {
		return r;
	}
	DBINFO("adding satff...", "");
	QSqlQuery q = QSqlQuery(db);

	q.prepare(INSERTINTO_STAFF);

	q.bindValue(":password", staff->Password().c_str());
	q.bindValue(":name", staff->Name().c_str());
	q.bindValue(":jobId", staff->Type());
	q.bindValue(":levelId", staff->Level());
	q.bindValue(":sex", staff->Sex());
	q.bindValue(":status", 1);
	q.bindValue(":cell", staff->cell().c_str());
	q.bindValue(":phone", staff->phone().c_str());
	q.bindValue(":address", staff->address().c_str());
	q.bindValue(":descrption", staff->Descrp().c_str());
	q.bindValue(":image", "");
	r = q.exec();
	db.close();
	DBINFO("add satff complete", "");
	return r;
}

bool ThreadDatabase::addSupperStaff(Staff* staff)
{
	db.setDatabaseName(DBNAME);
	if(!db.open()) {
		return false;
	}
	QSqlQuery q = QSqlQuery(db);
	
	DBINFO("creating super user...", "");
	q.prepare(INSERTINTO_STAFF_SUPER);
	q.bindValue(":id", SUPERUSERID);
	q.bindValue(":password", staff->Password().c_str());
	q.bindValue(":name", "科思美管理员");
	q.bindValue(":jobId", 0);
	q.bindValue(":levelId", 4);
	q.bindValue(":sex", 0);
	q.bindValue(":status", 1);
	q.bindValue(":cell", "88888888");
	q.bindValue(":phone", "66666666");
	q.bindValue(":address", "中华人民共和国");
	q.bindValue(":descrption", "我是科思美系统超级管理员");
	q.bindValue(":image", "");
	q.exec();
	DBINFO("create super user complete!", "");
	return true;
}