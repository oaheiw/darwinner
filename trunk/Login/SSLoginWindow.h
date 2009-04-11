#ifndef ENTRY_H
#define ENTRY_H

#include <QtGui/QDialog>
#include "ui_SSLoginWindow.h"

#include "DUIObserver.h"
class Message;


class SSLoginWindow : public QDialog, public DUIObserver
{
	Q_OBJECT

public:
	SSLoginWindow(QWidget *parent = 0, Qt::WFlags flags = 0 , DUIHandler* handler = 0);
	~SSLoginWindow();
	void OnEvent(Message& ev);

private:
	Ui::SSLoginWindowClass ui;


private slots:
	void on_pushButtonLogin_clicked();
};

#endif // ENTRY_H
