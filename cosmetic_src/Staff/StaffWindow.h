#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <list>
#include <map>
#include <string>
using namespace std;

#include "DUIObserver.h"

#include <QMainWindow>
#include "ui_StaffWindow.h"

class Staff;
class QEvent;
class Job;
class Level;
class Status;
class StaffDetail;
class QModelIndex;
class StaffConfiguration;
class SearchBox;

class StaffWindow : public QMainWindow , public DUIObserver
{
	Q_OBJECT

public:
	StaffWindow(QWidget *parent = 0);
	~StaffWindow();
	void OnEvent(Message& Msg);
	bool event(QEvent * ev);

protected:
	virtual bool eventFilter ( QObject * obj, QEvent * ev );

private:
	void addStaff(std::list<Staff> *staffList);
	void staffDetail(uint32 id);
	void getAllStaff();
	void getJobType();
	void getLevelType();
	void getStatusType();
	void removeStaff(uint32 id, string name);
	void Exit();
	void Logoff();
	void Menu();
	void removeStaff();
	void browseMyInfo();
	void changeMyPassword();
	void setLevels(list<Level>* levels);
	void setJobs(list<Job>* jobs);
	void staffConfig();
	void showSmallIcon(bool flag);
	void showTextLabel(bool flag);
	void showToolBar(bool flag);

	bool started;
	QFont font;
	map<uint32, Level> m_staffLevel;
	map<uint32, Job> m_staffType;
	map<uint32, Status> m_staffState;
	StaffDetail* staffDetailWidget;
	StaffConfiguration* config;
	SearchBox* m_searchBox;

	Ui::StaffWindowClass ui;

private slots:
	void dealAction(QAction*);
	void addStaff(Staff* staff, QByteArray& image);
	void modifyStaff(Staff* staff, QByteArray& image);
	void staffActivated(int row, int column, QVariant & data);
	void changePasswrod(string oldpw, string newpw);
};

#endif // STAFFWINDOW_H
