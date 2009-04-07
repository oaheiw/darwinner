#ifndef ENTRY_H
#define ENTRY_H

#include <QtGui/QDialog>
#include "ui_entry.h"

#include "DUIObserver.h"
class Message;


class entry : public QDialog, public DUIObserver
{
	Q_OBJECT

public:
	entry(QWidget *parent = 0, Qt::WFlags flags = 0 , DUIHandler* handler = 0);
	~entry();
	void OnEvent(Message& ev);

private:
	Ui::entryClass ui;


private slots:
	void on_pushButtonLogin_clicked();
};

#endif // ENTRY_H
