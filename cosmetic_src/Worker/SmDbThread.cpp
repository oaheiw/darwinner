#include "SmDbThread.h"
#include "common.h"
#include "messagedef.h"
#include "Message.h"
 #include <QSqlQuery>
#include <QVariant>
#include "dbquery.h"
#include <fstream>
#include "Staff.h"
#include "Job.h"
#include "Level.h"
#include "Status.h"
#include "Singleton.h"


SmDbThread::SmDbThread(QObject *parent , QThread::Priority priority)
:DbThread(parent, priority)
{
	setDbServer("QSQLITE", DBCONNECTION_SM, "", "", "", 0);
}

SmDbThread::~SmDbThread()
{

}

void SmDbThread::WorkerThreadMain(Message& Action) {
	DBHEX("sm db thread processing action: ", Action.type());
	switch(Action.type()) {
		case ACTION_GEALLSTAFF:
		{
			m_tempMsg = new Message(EVENT_ALLSTAFF, getAllStaffs());
			break;
		}
		case ACTION_GETSTAFF:
		{
			uint32* id = static_cast<uint32*>(Action.data());
			m_tempMsg = new Message(EVENT_STAFF, getStaff(*id));
			delete id;
			break;
		}
		case ACTION_ADDSTAFF:
		{
			Staff* staff = static_cast<Staff*>(Action.data());
			QByteArray* image = static_cast<QByteArray*>(Action.data2());
			Staff* addedStaff = NULL;
			if(addStaff(staff)) {
				addedStaff = getStaff(staff->id());
			}
			m_tempMsg = new Message(EVENT_STAFFADDED, addedStaff);
			if(NULL != image && !image->isEmpty() && addedStaff->id() != 0) {
				if(setImage(addedStaff->id(), *image))
					m_tempMsg->setData2(getImage(addedStaff->id()));
			}
			delete staff;
			image->clear();
			delete image;
			break;
		}
		case ACTION_SETSTATUSTYPE:
		{
			list<Status>* statusList = static_cast<list<Status>*>(Action.data());
			list<Status>* result = new list<Status>;
			list<Status>::iterator it = statusList->begin();
			while(statusList->end() != it) {
				if(!addStatusType(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete statusList;
			m_tempMsg = new Message(EVENT_SETSTATUSTYPE, result);
			break;
		}
		case ACTION_SETJOBTYPE:
		{
			list<Job>* jobList = static_cast<list<Job>*>(Action.data());
			list<Job>* result = new list<Job>;
			list<Job>::iterator it = jobList->begin();
			while(jobList->end() != it) {
				if(!addJobType(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete jobList;
			m_tempMsg = new Message(EVENT_SETJOBTYPE, result);
			break;
		}
		case ACTION_REMOVEJOBTYPE:
		{
			list<Job>* jobList = static_cast<list<Job>*>(Action.data());
			list<Job>* result = new list<Job>;
			list<Job>::iterator it = jobList->begin();
			while(jobList->end() != it) {
				if(!removeJob(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete jobList;
			m_tempMsg = new Message(EVENT_REMOVEJOBTYPE, result);
			break;
		}
		case ACTION_SETLEVELTYPE:
		{
			list<Level>* levelList = static_cast<list<Level>*>(Action.data());
			list<Level>* result = new list<Level>;
			list<Level>::iterator it = levelList->begin();
			while(levelList->end() != it) {
				if(!addLevelType(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete levelList;
			m_tempMsg = new Message(EVENT_SETLEVELTYPE, result);
			break;
		}
		case ACTION_REMOVELEVELTYPE:
		{
			list<Level>* levelList = static_cast<list<Level>*>(Action.data());
			list<Level>* result = new list<Level>;
			list<Level>::iterator it = levelList->begin();
			while(levelList->end() != it) {
				if(!removeLevel(&(*it)))
					result->push_back(*it);
				it++;
			}
			delete levelList;
			m_tempMsg = new Message(EVENT_REMOVELEVELTYPE, result);
			break;
		}
		case ACTION_CHANGEPASSWORD:
		{
			list<string>* pwList = static_cast<list<string>*>(Action.data());
			uint32 id = Singleton<Staff>::instance()->id();
			string oldpw = pwList->front();
			string newpw = pwList->back();
			m_tempMsg = new Message(EVENT_CHANGEPASSWORD, changePassword(id, oldpw, newpw));
			delete pwList;
			break;
		}

		case ACTION_GETJOBTYPE:
		{
			m_tempMsg = new Message(EVENT_JOBTYPE, getJobs());
			break;
		}
		case ACTION_GETLEVELTYPE:
		{
			m_tempMsg = new Message(EVENT_LEVELTYPE, getLevels());
			break;
		}
		case ACTION_GETSTATUSTYPE:
		{
			m_tempMsg = new Message(EVENT_STATUSTYPE, getStatus());
			break;
		}
		case ACTION_MODIFYSTAFF:
		{
			Staff* staff = static_cast<Staff*>(Action.data());
			QByteArray* image = static_cast<QByteArray*>(Action.data2());
			Staff* modifieddStaff = NULL;
			if(modifyStaff(staff)) {
				modifieddStaff = getStaff(staff->id());
			}
			m_tempMsg = new Message(EVENT_STAFFMODIFIED, modifieddStaff);
			if(NULL != image && !image->isEmpty() && modifieddStaff->id() != 0) {
				if(setImage(modifieddStaff->id(), *image))
					m_tempMsg->setData2(getImage(modifieddStaff->id()));
			}
			delete staff;
			break;
		}
		case ACTION_REMOVESTAFF:
		{
			uint32* id = static_cast<uint32*>(Action.data());
			m_tempMsg = new Message(EVENT_STAFFREMOVED, removeStaff(*id));
			delete id;
			break;
		}
		case ACTION_GETPICTURE:
		{
			uint32* id = static_cast<uint32*>(Action.data());
			m_tempMsg = new Message(EVENT_GETPICTURE, getImage(*id));
			delete id;
			break;
		}
		default:
			break;	
	}
	if(NULL != m_tempMsg) {
		postEvent(m_tempMsg, EventDb);
		m_tempMsg = NULL;
	}
}

Staff* SmDbThread::getStaff(uint32 id) 
{
	Staff* temp = NULL;
	if(0 == id || !openDb(DBNAME)){//id 0 staff surely not in the database
		return temp;
	}
	DBDEC("getting one staff:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	QString query = QString(SELECT_STAFF_BYID_NOIMAGE).arg(id);
	if(q.exec(query)){
		if(q.next()) {
			temp = new Staff();
			temp->setid((uint32)q.value(0).toUInt());
			temp->setpassword(string(q.value(1).toByteArray().data()));
			temp->setname(string(q.value(2).toByteArray().data()));
			temp->settype((uint32)q.value(3).toUInt());
			temp->setlevel((uint32)q.value(4).toUInt());
			temp->setsex((uint32)q.value(5).toUInt());
			temp->setbonus((uint32)q.value(6).toUInt());
			temp->setstatus((uint32)q.value(7).toUInt());
			temp->setcell(string(q.value(8).toByteArray().data()));
			temp->setphone(string(q.value(9).toByteArray().data()));
			temp->setaddress(string(q.value(10).toByteArray().data()));
			temp->setdescription(string(q.value(11).toByteArray().data()));
			temp->setrating(rand()%100);
			//rating to be relized;
		}
	}
	closeDb();
	DBDEC("get one staff completed:", id);
	return temp;
}

bool SmDbThread::addStaff(Staff* staff)
{
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBHEX("adding satff...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	q.prepare(INSERTINTO_STAFF);

	q.bindValue(":password", staff->password().c_str());
	q.bindValue(":name", staff->name().c_str());
	q.bindValue(":jobId", staff->type());
	q.bindValue(":levelId", staff->level());
	q.bindValue(":sex", staff->sex());
	q.bindValue(":bonus", staff->bonus());
	q.bindValue(":status", staff->status());
	q.bindValue(":cell", staff->cell().c_str());
	q.bindValue(":phone", staff->phone().c_str());
	q.bindValue(":address", staff->address().c_str());
	q.bindValue(":description", staff->description().c_str());
	r = q.exec();
	if(r) {
		q.exec("SELECT MAX(id) FROM staff");
		if(q.next()) staff->setid(q.value(0).toUInt());
		QString setpw = QString(UPDATE_STAFFPASWORD_BYID).arg(staff->id()).arg(staff->id());
		r = q.exec(setpw);
	}
	closeDb();
	DBDEC("add satff complete", staff->id());
	return r;
}

bool SmDbThread::setImage(uint32 id, QByteArray& image)
{
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBDEC("setting image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	QString check = QString(GET_STAFFIMAGE_BYID).arg(id);
	if(q.exec(check)) {
		if(q.next())
			q.exec(QString(DELETE_STAFFIMAGE).arg(id));
	}

	q.prepare(INSERT_STAFFIMAGE);
	q.bindValue(":id", id);
	q.bindValue(":data", image, QSql::Binary | QSql::In);
	r = q.exec();
	closeDb();
	DBDEC("set image complete", r);
	return r;

}

QByteArray* SmDbThread::getImage(uint32 id)
{
	QByteArray* image = new QByteArray;
	image->clear();
	
	if(0 == id || !openDb(DBNAME)) {//id 0 staff surely not in the database
		return image;
	}
	
	DBDEC("getting image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	QString check = QString(CHECK_STAFFIMAGE_BYID).arg(id);
	if(q.exec(check)) {
		if(!q.next()) return image;
	}

	QString get = QString(GET_STAFFIMAGE_BYID).arg(id);
	if(q.exec(get)) {
		if(q.next()) {
			if(NULL != q.value(0).toByteArray().data())
				*image = q.value(0).toByteArray();
		}
	}
	
	q.clear();
	closeDb();
	DBHEX("get image complete", "");
	return image;
}

uint32* SmDbThread::removeStaff(uint32 id)
{
	uint32* r = new uint32(id);
	
	if(!openDb(DBNAME)) {
		*r = 0;
		return r;
	}
	DBDEC("removing satff...", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	QString remove = QString(DELETE_STAFF_BYID).arg(id);
	if(!q.exec(remove)) 
	{
		*r = 0;
	} else {
		deleteImage(id);
	}
	closeDb();
	DBDEC("remove satff complete", *r);
	return r;
}


bool SmDbThread::modifyStaff(Staff* staff)
{
	bool r =false;
	if(0 == staff->id() || !openDb(DBNAME)) {
		return r;
	}
	DBDEC("modifying satff...", staff->id());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	QString check = QString(CHECK_STAFF_BYID).arg(staff->id());
	q.exec(check);
	if(!q.isActive()) return r;

	QString modifstr = QString(UPDATA_STAFF_BASIC).arg(staff->name().c_str()).arg(staff->type()).arg(staff->level()).arg(staff->sex()).arg(staff->bonus()).arg(staff->status()).arg(staff->cell().c_str()).arg(staff->phone().c_str()).arg(staff->address().c_str()).arg(staff->description().c_str()).arg(staff->id()); 
	r = q.exec(modifstr);
	closeDb();
	
	DBDEC("modify satff complete", r);
	return r;
}

bool SmDbThread::addJobType(Job* job)
{
	bool r = false;
	
	if(!openDb(DBNAME)) {
		return r;
	}
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	QString qstring = QString(SELECT_JOB_BYID).arg(job->id());
	q.exec(qstring);
	if (q.next()) 
	{
		QString update = QString(UPDATA_JOB).arg(job->name().c_str()).arg(job->profit()).arg(job->baseSalary()).arg(job->description().c_str()).arg(job->id());
		r = q.exec(update);
	}
	else
	{
		q.prepare(INSERTINTO_JOB_TABLE);
		q.bindValue(":name", job->name().c_str());
		q.bindValue(":profit", job->profit());
		q.bindValue(":baseSalary", job->baseSalary());
		q.bindValue(":description", job->description().c_str());
		r = q.exec();
	}
	closeDb();
	return r;
}

bool SmDbThread::addLevelType(Level* level)
{
	bool r = false;
	
	if(!openDb(DBNAME)) {
		return r;
	}
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	QString qstring = QString(SELECT_LEVEL_BYID).arg(level->id());
	q.exec(qstring);
	if (q.next()) 
	{
		QString update = QString(UPDATA_LEVEL).arg(level->name().c_str()).arg(level->profit()).arg(level->baseSalary()).arg(level->description().c_str()).arg(level->id());
		r = q.exec(update);
	}
	else
	{
		q.prepare(INSERTINTO_LEVEL_TABLE);
		q.bindValue(":name", level->name().c_str());
		q.bindValue(":profit", level->profit());
		q.bindValue(":baseSalary", level->baseSalary());
		q.bindValue(":description", level->description().c_str());
		r = q.exec();
	}
	closeDb();
	return r;
}

bool SmDbThread::addStatusType(Status* status)
{
	bool r = false;
	
	if(!openDb(DBNAME)) {
		return r;
	}
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	QString qstring = QString(SELECT_STATUS_BYID).arg(status->id());
	q.exec(qstring);
	if (q.next()) 
	{
		QString update = QString(UPDATA_STATUS).arg(status->name().c_str()).arg(status->description().c_str()).arg(status->id());
		r = q.exec(update);
	}
	else
	{
		q.prepare(INSERTINTO_STATUS_TABLE);
		q.bindValue(":name", status->name().c_str());
		q.bindValue(":description", status->description().c_str());
		r = q.exec();
	}
	closeDb();
	return r;
}


list<Staff>* SmDbThread::getAllStaffs()
{
	list<Staff>* r = new list<Staff>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}
	
	DBHEX("geting all staffs...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	q.exec(SELECT_STAFF_NOIMAGE);
	Staff temp;
	
	while (q.next()) {
		temp.setid((uint32)q.value(0).toUInt());
		temp.setpassword(string(q.value(1).toByteArray().data()));
		temp.setname(string(q.value(2).toByteArray().data()));
		temp.settype((uint32)q.value(3).toUInt());
		temp.setlevel((uint32)q.value(4).toUInt());
		temp.setsex((uint32)q.value(5).toUInt());
		temp.setbonus((uint32)q.value(6).toUInt());
		temp.setstatus((uint32)q.value(7).toUInt());
		temp.setcell(string(q.value(8).toByteArray().data()));
		temp.setphone(string(q.value(9).toByteArray().data()));
		temp.setaddress(string(q.value(10).toByteArray().data()));
		temp.setdescription(string(q.value(11).toByteArray().data()));
		temp.setrating(rand()%100);
		//rating to be relized;
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all staffs. amount: ", r->size());
	return r;
}

list<Job>* SmDbThread::getJobs()
{
	list<Job>* r = new list<Job>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}
	DBHEX("getting all jobs", r->size());
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	q.exec(SELECT_JOB_ALL);
	Job temp;

	while (q.next()) {
		temp.setId(q.value(0).toUInt());
		temp.setName(q.value(1).toByteArray().data());
		temp.setProfit(q.value(2).toUInt());
		temp.setBaseSalary(q.value(3).toUInt());
		temp.setDescription(q.value(4).toByteArray().data());
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all jobs. amount: ", r->size());
	return r;
}

list<Level>* SmDbThread::getLevels()
{
	list<Level>* r = new list<Level>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}
	DBHEX("getting all levels...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	q.exec(SELECT_LEVEL_ALL);
	Level temp;

	while (q.next()) {
		temp.setId(q.value(0).toUInt());
		temp.setName(q.value(1).toByteArray().data());
		temp.setProfit(q.value(2).toUInt());
		temp.setBaseSalary(q.value(3).toUInt());
		temp.setDescription(q.value(4).toByteArray().data());
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all levels. amount: ", r->size());
	return r;
}

list<Status>* SmDbThread::getStatus()
{
	list<Status>* r = new list<Status>;
	r->clear();
	if(!openDb(DBNAME)){
		return r;
	}
	DBHEX("getting all status...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	q.exec(SELECT_STATUS_ALL);
	Status temp;

	while (q.next()) {
		temp.setId(q.value(0).toUInt());
		temp.setName(q.value(1).toByteArray().data());
		temp.setDescription(q.value(2).toByteArray().data());
		r->push_back(temp);
	}
	closeDb();
	DBDEC("get all status. amount: ", r->size());
	return r;
}

int* SmDbThread::changePassword(uint32 id, string oldpw, string newpw)
{
	int* r =new int(ERROR_PASSWORD_WRONG);

	if(!openDb(DBNAME)) {
		DBHEX("open db failed.", "");
		return r;
	}
	
	DBHEX("changing password...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));
	

	QString getold = QString(GET_STAFFPASSWORD_BYID).arg(id);
	if(q.exec(getold)) {
		if(q.next()) {
			if(oldpw != string(q.value(0).toByteArray().data())) return r;
		}else{
			*r = ERROR_DBERROR;
			return r;
		}
	} else {
		*r = ERROR_DBERROR;
		return r;
	}

	QString setnew = QString(UPDATE_STAFFPASWORD_BYID).arg(newpw.c_str()).arg(id);
	if(q.exec(setnew)) {
		*r = ERROR_NO_ERROR;
	} else {
		*r = ERROR_DBERROR;
	}
	closeDb();
	DBDEC("change password complete", r);
	return r;
}

bool SmDbThread::removeJob(Job* id)
{
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}
	DBHEX("removing job...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	QString check = QString(CHECK_JOB_BYID).arg(id->id());
	if(q.exec(check)) {
		if(q.next())
			return r;
	}

	QString remove = QString(DELETE_JOB_BYID).arg(id->id());
	r = q.exec(remove);
	closeDb();
	DBDEC("remove job complete", r);
	return r;
}

bool SmDbThread::removeLevel(Level* id)
{
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}

	DBHEX("removing level...", "");
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	QString check = QString(CHECK_LEVEL_BYID).arg(id->id());
	if(q.exec(check)) {
		if(q.next())
			return r;
	}

	QString remove = QString(DELETE_LEVEL_BYID).arg(id->id());
	r = q.exec(remove);
	closeDb();
	DBDEC("remove job complete", r);
	return r;
}

bool SmDbThread::deleteImage(uint32 id)
{
	bool r =false;
	if(!openDb(DBNAME)) {
		return r;
	}

	DBDEC("delete image for:", id);
	QSqlQuery q = QSqlQuery(getDb(DBCONNECTION_SM));

	r= q.exec(QString(DELETE_STAFFIMAGE).arg(id));
	DBDEC("delete image compltet:", r);
	return r;
}

