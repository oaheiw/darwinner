#ifndef BUSINESSMANAGEMENTUI_H
#define BUSINESSMANAGEMENTUI_H

#include <QMainWindow>
#include "ui_BusinessManagementUI.h"
#include <QtGui>

#include "DUIObserver.h"

#include <list>
#include <map>
#include <string>
class QModelIndex;
class QEvent;

using namespace std;


class BusinessManagementUI : public QMainWindow, public DUIObserver
{
	Q_OBJECT

public:
	BusinessManagementUI(QWidget *parent = 0);
	~BusinessManagementUI();
	void OnEvent(Message& Msg);
	bool event(QEvent * ev);

protected:
	virtual bool eventFilter (QObject * obj, QEvent * ev);

private:
	Ui::BusinessManagementUIClass ui;
};

#endif // BUSINESSMANAGEMENTUI_H
