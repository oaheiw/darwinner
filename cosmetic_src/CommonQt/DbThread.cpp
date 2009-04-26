#include "DbThread.h"
#include <QString>

DbThread::DbThread(QObject *parent, QThread::Priority priority)
: WorkerThread(parent, priority)
{

}

DbThread::~DbThread()
{
}

void DbThread::setDbServer(const char* dbtype, const char* connection, const char* hostname, const char* username, const char* password, int port)
{
	DBINFO("add connection: ", connection);
	db = QSqlDatabase::addDatabase(dbtype, QString(connection));
DBINFO("DEBUG 1", "");
/*
	db.setHostName(hostname);
	db.setUserName(username);
	db.setPassword(password);
	db.setPort(port);
	
	db.open();
	
	db = QSqlDatabase::database(connection);
	*/
	DBINFO("add connection complete", connection);
}

bool DbThread::openDb(const char* dbname)
{
//	DBINFO("opening db:", dbname);
//	DBINFO("db connection: ", db.connectionName().toLocal8Bit().data());
	db.setDatabaseName(dbname);
	return db.open();
}

void DbThread::closeDb()
{
	db.close();
}

QSqlDatabase& DbThread::getDb(const char* connection)
{
			DBINFO("debug 7", "");
	db = QSqlDatabase::database(connection);
			DBINFO("debug 8", "");
	return db;
}
