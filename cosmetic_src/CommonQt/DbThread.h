#ifndef DBTHREAD_H
#define DBTHREAD_H

#include "WorkerThread.h"
#include <QSqlDatabase>

#if defined(_BASIC) | defined(_ADVANCED) | defined(_DEMO)
#define DBTYPE "QSQLITE"
#else
#define DBTYPE "QMYSQL"
#endif

class DbThread : public WorkerThread
{
public:
	DbThread(QObject *parent = 0, 
		QThread::Priority priority = QThread::NormalPriority);
	virtual ~DbThread();

protected:
	void setDbServer
		(const char* dbtype, const char* connection, 
		const char* hostname, const char* username, 
		const char* password, int port);
	bool openDb(const char* dbname);
	void closeDb();
	QSqlDatabase& getDb(const char* connection);

private:
	QSqlDatabase db;	
};

#endif // DBTHREAD_H
