#ifndef ThreadDatabase_h
#define ThreadDatabase_h

#include "common.h"

#ifdef D_DEMO
#include "Staff.h"
#include <vector>
#endif
#include <QThread.>
#include <QMutex>
#include <QWaitCondition>
class Message;
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
#ifdef D_DEMO
	vector<Staff> stuffList;
#endif

};

#endif