#ifndef ThreadDatabase_h
#define ThreadDatabase_h

#include "DbThread.h"
class Message;
class Staff;
class Job;
class Level;
class Status;

class SmDbThread : public DbThread
{
public:
	SmDbThread(QObject *parent = 0, QThread::Priority priority = QThread::NormalPriority);
	virtual ~SmDbThread();

protected:
	virtual void WorkerThreadMain(Message& action);
	
 private:
	Staff* m_loggedstaff;
	bool initDb();
	Staff* getStaff(uint32 id);
	uint32* removeStaff(uint32 id);
	bool removeJob(Job* id);
	bool removeLevel(Level* id);
	bool addStaff(Staff* staff);
	bool modifyStaff(Staff* staff);
	bool checkDd();
	bool addSupperStaff(Staff* staff);
	bool addJobType(Job* job);
	bool addLevelType(Level* level);
	bool addStatusType(Status* status);
	int* changePassword(string oldpw, string newpw);
	list<Staff>* getAllStaffs();
	list<Job>* getJobs();
	list<Level>* getLevels();
	list<Status>* getStatus();
	bool setImage(uint32 id, QByteArray& image);
	QByteArray* getImage(uint32 id);
	bool deleteImage(uint32 id);
//	bool openDb();
//	void cleseDb();
};

#endif