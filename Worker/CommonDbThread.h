#ifndef COMMONDB_H
#define COMMONDB_H

#include "DbThread.h"
class Staff;
#include <string>
using namespace std;

class CommonDbThread :public DbThread
{
public:
	CommonDbThread(QObject *parent = 0, QThread::Priority priority = QThread::NormalPriority);
	virtual ~CommonDbThread(void);

protected:
	virtual void WorkerThreadMain(Message& action);
	
 private:
	bool initDb();
	bool checkDd();
	bool addSupperStaff(Staff* staff);
	bool getLoggedStaff(uint32 id);
	string getPassword(uint32 id);
	Staff* m_loggedStaff;
	QByteArray* m_loggedStaffImage;
};

#endif
