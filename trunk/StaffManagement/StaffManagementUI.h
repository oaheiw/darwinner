#ifndef STAFFMANAGEMENT_H
#define STAFFMANAGEMENT_H

#include "staffmanagement_global.h"
#include "IEventObserver.h"
#include "ui_StaffMainWindow.h"
#include "DUIObserver.h"
#include <QtGui>

class STAFFMANAGEMENT_EXPORT StaffManagementUI : public QMainWindow, public DUIObserver
{
	Q_OBJECT
public:
	StaffManagementUI();
	~StaffManagementUI();
	void OnEvent(Message& Msg);

private:
	Ui::MainWindow ui;
	QAbstractItemModel* m_stuffDataModel;
	QSortFilterProxyModel* m_sortProxyModel;


private slots:
	void on_pushButtonExit_clicked();
	void on_pushButtonLogoff_clicked();
	void on_pushButtonBack_clicked();
};

#endif // STUFFMANAGEMENT_H
