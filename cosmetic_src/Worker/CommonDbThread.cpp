#include "CommonDbThread.h"
#include "common.h"
#include "messagedef.h"
#include "Message.h"
 #include <QSqlQuery>
#include <QVariant>
#include "dbquery.h"
#include <fstream>
#include "Staff.h"

CommonDbThread::CommonDbThread(QObject *parent , QThread::Priority priority)
:DbThread(parent, priority)
{
	m_loggedStaff = new Staff();
	m_loggedStaff->clear();
	m_loggedStaffImage = new QByteArray();
	m_loggedStaffImage->clear();
	setDbServer("QSQLITE", DBCONNECTION_COMMON, "", "", "", 0);
}

CommonDbThread::~CommonDbThread()
{

}

void CommonDbThread::WorkerThreadMain(Message& Action) {
	DBHEX("common db thread processing action: ", Action.type());
	switch(Action.type()) {
		case ACTION_SYSTEM_START:
		{
			if(checkDd()) {
				m_tempMsg = new Message(EVENT_SYSTEM_START);	
			}else{
				m_tempMsg = new Message(EVENT_WIZARD);
			}			
			break;
		}
		case ACTION_INIT_DB:
		{
			initDb();
			break;
		}
		case ACTION_LOGIN:
		{
			Staff* staffIncome = static_cast<Staff*>(Action.data());
			string passwordInDb = getPassword(staffIncome->id());
			int* r = new int(ERROR_NO_ERROR);
			if(!passwordInDb.empty() && staffIncome->password() == passwordInDb) 
			{
				getLoggedStaff(staffIncome->id());
				*r = ERROR_NO_ERROR;
			} else {
				*r = ERROR_PASSWORD_WRONG;
			}
			m_tempMsg = new Message(EVENT_LOGGEDIN, r, m_loggedStaff);
			delete staffIncome;
			break;
		}
		case ACTION_LOGOFF:
		{
			m_loggedStaff->clear();
			m_loggedStaffImage->clear();
			m_tempMsg = new Message(EVENT_LOGGEDOFF);
			break;
		}
		case ACTION_SETSUPERUSER:
		{
			Staff* staff = static_cast<Staff*>(Action.data());
			addSupperStaff(staff);
			delete staff;
			m_tempMsg = new Message(EVENT_SETSUPERUSER);
			break;
		}
		case ACTION_GETLOGGEDSTAFF:
		{
			m_tempMsg = new Message(EVENT_LOGGEDSTAFF, m_loggedStaff, m_loggedStaffImage);
			break;
		}
		default:
			break;	
	}
	//be sure the m_tempMsg is NOT NULL!!!
	if(NULL != m_tempMsg) {
		postEvent(m_tempMsg, EventDb);
		m_tempMsg = NULL;
	}
}

bool CommonDbThread::initDb()
{
	if(!openDb(DBNAME)) {
		return false;
	}
	
	DBHEX("initializing database...", "");

	m_tempMsg = new Message(EVENT_INIT);
	if(NULL != m_tempMsg) {
		postEvent(m_tempMsg, EventDb);
		m_tempMsg = NULL;
	}	
	
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_COMMON));
	//staff mgnt
	q.exec(CREATE_STAFF_TABLE);
	q.exec(CREATE_STAFFIMAGE_TABLE);
	q.exec(CREATE_JOB_TABLE);
	q.exec(CREATE_LEVET_TABLE);
	q.exec(CREATE_STATUS_TABLE);
	//bussiness mgnt
	q.exec(CREATE_BUSINESSTYPE_TABLE);
	q.exec(CREATE_BUSINESS_TABLE);
	q.exec(CREATE_BUSINESSIMAGE_TABLE);
	q.exec(CREATE_ORDERS_TABLE);
	q.exec(CREATE_TASKS_TABLE);
	//customer mgnt
	q.exec(CREATE_CUSTOMERLEVEL_TABLE);
	q.exec(CREATE_CUSTOMER_TABLE);
	q.exec(CREATE_CUSTOMERIMAGE_TABLE);

	closeDb();

	m_tempMsg = new Message(EVENT_INIT_FINISHED);
	if(NULL != m_tempMsg) {
		postEvent(m_tempMsg, EventDb);
		m_tempMsg = NULL;
	}
	DBHEX("databese initialized.", "");
	return true;
}

bool CommonDbThread::checkDd()
{
	bool re = false;
	bool exist;
	int length= 0;
	char* SQLiteMark;
	int isSQLite = 0;
	fstream testfile;
	testfile.open (DBFILE, fstream::in | fstream::out | fstream::app | fstream::binary);
	exist = testfile.is_open();
	if(exist) {
	  testfile.seekg(0, ios::end);
	  length = testfile.tellg();
	  testfile.seekg(0, ios::beg);
	  //now, using crypto sqlite. method below obsolete
	  /*
	  SQLiteMark = new char[SQLITEMARKLEN];
	  memset(SQLiteMark, 0, SQLITEMARKLEN);
	  testfile.read(SQLiteMark, SQLITEMARKLEN);
	  isSQLite = memcmp(SQLiteMark, SQLITEMARK, SQLITEMARKLEN);
	  */
	  testfile.close();
	}
	  
	if(!exist | 0 == length | 0 != isSQLite) {//first time running
		DBHEX("database file not exist or corrupt, creat new one.", "")
		remove(DBFILE);
		re = false;
	} else {//database exists. check super user
		testfile.close();
		openDb(DBNAME);
		QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_COMMON));
		QString query = QString("SELECT id FROM staff WHERE id = %1").arg(SUPERUSERID);
		q.exec(query);
		if(!q.next()) {
			re = false;
		}
		else {
			re = true;
		}
		closeDb();
	}
	return re;
}

string CommonDbThread::getPassword(uint32 id) 
{
	string password;
	password.clear();
	if(!openDb(DBNAME)){
		return password;
	}
	DBHEX("getting password for: ", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_COMMON));
	QString query = QString(GET_STAFFPASSWORD_BYID).arg(id);
	if(q.exec(query)){
		if(q.next()) {
			password = string(q.value(0).toByteArray().data());
		}
	}
	closeDb();
	DBHEX("get password completed:", password);
	return password;
}

bool CommonDbThread::addSupperStaff(Staff* staff)
{
	bool r = false;
	if(!openDb(DBNAME)) {
		return r;
	}
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_COMMON));
	
	DBHEX("creating super user...", "");
	q.prepare(INSERTINTO_STAFF_SUPER);
	q.bindValue(":id", SUPERUSERID);
	q.bindValue(":password", staff->password().c_str());
	q.bindValue(":name", "超级用户");
	q.bindValue(":jobId", 1);
	q.bindValue(":levelId", 1);
	q.bindValue(":sex", 1);
	q.bindValue(":status", 1);
	q.bindValue(":cell", "88888888");
	q.bindValue(":phone", "66666666");
	q.bindValue(":address", "思索软件工作室");
	q.bindValue(":description", "这是科思美系统超级账户，请不要将此账户用作日常运作账户。");
	r = q.exec();
	DBHEX("create super user complete!", r);
	return r;
}

bool CommonDbThread::getLoggedStaff(uint32 id) 
{
	bool r = false;
	if(!openDb(DBNAME)){
		return r;
	}

	DBHEX("getting logged staff...", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_COMMON));
	QString query = QString(SELECT_STAFF_BYID_NOIMAGE).arg(id);
	if(q.exec(query)){
		if(q.next()) {
			m_loggedStaff->setid((uint32)q.value(0).toUInt());
			m_loggedStaff->setpassword(string(q.value(1).toByteArray().data()));
			m_loggedStaff->setname(string(q.value(2).toByteArray().data()));
			m_loggedStaff->settype((uint32)q.value(3).toUInt());
			m_loggedStaff->setlevel((uint32)q.value(4).toUInt());
			m_loggedStaff->setsex((uint32)q.value(5).toUInt());
			m_loggedStaff->setbonus((uint32)q.value(6).toUInt());
			m_loggedStaff->setstatus((uint32)q.value(7).toUInt());
			m_loggedStaff->setcell(string(q.value(8).toByteArray().data()));
			m_loggedStaff->setphone(string(q.value(9).toByteArray().data()));
			m_loggedStaff->setaddress(string(q.value(10).toByteArray().data()));
			m_loggedStaff->setdescription(string(q.value(11).toByteArray().data()));
		}
	}

	QString get = QString(GET_STAFFIMAGE_BYID).arg(id);
	if(q.exec(get)) {
		if(q.next()) {
			*m_loggedStaffImage = q.value(0).toByteArray();
		}
	}
	
	closeDb();
	DBHEX("get logged staff completed:", id);
	return r;
}

