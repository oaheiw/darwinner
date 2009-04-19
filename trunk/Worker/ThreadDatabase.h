#ifndef ThreadDatabase_h
#define ThreadDatabase_h

#include "common.h"

#include <QThread.>
#include <QMutex>
#include <QWaitCondition>
#include <QSqlDatabase>
class Message;
class Staff;
class Job;
class Level;
class Status;
#include <list>
#include <string>
using namespace std;

class ThreadDatabase : public QThread
{

	Q_OBJECT
public:
	ThreadDatabase(QObject *parent = 0);
	~ThreadDatabase();
	void QueueAction(Message& action);

protected:
	void run();

protected:
	QMutex mutex;
    QWaitCondition bufferEmpty;
	list<Message> m_listActionBuffer;
	Message* m_tempMsg;

 private:
	QSqlDatabase db;
	Staff* m_loggedstaff;
	bool initDb();
	Staff* getStaff(uint32 id);
	uint32* removeStaff(uint32 id);
	bool addStaff(Staff* staff);
	bool modifyStaff(Staff* staff);
	bool checkDd();
	bool addSupperStaff(Staff* staff);
	bool addJobType(Job* job);
	bool addLevelType(Level* level);
	bool addStatusType(Status* status);
	bool changePassword(string oldpw, string newpw);
	list<Staff>* getAllStaffs();
	list<Job>* getJobs();
	list<Level>* getLevels();
	list<Status>* getStatus();
};

#endif