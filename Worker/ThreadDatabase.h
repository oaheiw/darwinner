#ifndef ThreadDatabase_h
#define ThreadDatabase_h

#include "common.h"

#include <QThread.>
#include <QMutex>
#include <QWaitCondition>
#include <QSqlDatabase>
class Message;
class Staff;
#include <list>
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
	bool initDb();
	Staff* getStaff(uint32 id);
	bool addStaff(Staff* staff);
	bool checkDd();
};

#endif