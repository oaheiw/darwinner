#ifndef STUFFMANAGEMENT_H
#define STUFFMANAGEMENT_H

#include "stuffmanagement_global.h"
#include "IEventObserver.h"
#include "ui_StuffMainWindow.h"
#include <QtGui>

class STUFFMANAGEMENT_EXPORT StuffManagement : public QMainWindow, public IEventObserver
{
	Q_OBJECT
public:
	StuffManagement();
	~StuffManagement();
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
