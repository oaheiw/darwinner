#ifndef STAFFMANAGEMENT_H
#define STAFFMANAGEMENT_H

#include "staffmanagement_global.h"
#include "ui_StaffMainWindow.h"
#include "DUIObserver.h"
#include "Staff.h"
#include <QtGui>
#include <QEvent>
#include <list>
using namespace std;

class STAFFMANAGEMENT_EXPORT StaffManagementUI : public QMainWindow, public DUIObserver
{
	Q_OBJECT
public:
	StaffManagementUI();
	~StaffManagementUI();
	void OnEvent(Message& Msg);

protected:
	void showEvent ( QShowEvent * event );
	void closeEvent ( QCloseEvent * event );

private:
	Ui::MainWindow ui;
	QAbstractItemModel* m_stuffDataModel;
	QSortFilterProxyModel* m_sortProxyModel;
	void addStaff(list<Staff> *staffList);
	void SettingFont();

private slots:
	void Exit();
	void Logoff();
	void Menu();

     void filterRegExpChanged();
     void filterColumnChanged();
     void sortChanged();
};

#endif // STUFFMANAGEMENT_H
