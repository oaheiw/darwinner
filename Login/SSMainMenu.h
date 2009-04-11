#ifndef DARWINMAIN_H
#define DARWINMAIN_H

#include <QDialog>
#include "ui_SSMainMenu.h"

#include "DUIObserver.h"

class SSMainMenu : public QDialog, public DUIObserver
{
	Q_OBJECT

public:
	SSMainMenu(QWidget *parent = 0, DUIHandler* handler = 0);
	~SSMainMenu();
	void OnEvent(Message& ev) ;

private:
	Ui::SSMenuWindowClass ui;


private slots:
	void on_pushButtonStaffMgnt_clicked();
	void on_pushButtonLogoff_clicked();
};

#endif // DARWINMAIN_H
