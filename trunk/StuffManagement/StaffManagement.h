#ifndef STUFFMANAGEMENT_H
#define STUFFMANAGEMENT_H

#include "staffmanagement_global.h"
#include "IEventObserver.h"
#include "ui_StaffMainWindow.h"
#include "DUIObserver.h"
#include <QtGui>

class STAFFMANAGEMENT_EXPORT StaffManagement : public QMainWindow, public DUIObserver
{
	Q_OBJECT
public:
	StaffManagement();
	~StaffManagement();
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
