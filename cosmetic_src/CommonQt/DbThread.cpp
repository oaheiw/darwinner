#include "DbThread.h"

DbThread::DbThread(QObject *parent, QThread::Priority priority)
: WorkerThread(parent, priority)
{

}

DbThread::~DbThread()
{
}

void DbThread::setDbServer(const char* dbtype, const char* connection, const char* hostname, const char* username, const char* password, int port)
{
	db = QSqlDatabase::addDatabase(dbtype, connection);

	db.setHostName(hostname);
	db.setUserName(username);
	db.setPassword(password);
	db.setPort(port);
	
	db = QSqlDatabase::database(connection, false);

	DBHEX("add connection complete", connection);
}

bool DbThread::openDb(const char* dbname)
{
	db.setDatabaseName(dbname);
	return db.open();
}

void DbThread::closeDb()
{
	db.close();
}

QSqlDatabase& DbThread::getDb(const char* connection)
{
	return db;
}

