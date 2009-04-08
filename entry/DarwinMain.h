#ifndef DARWINMAIN_H
#define DARWINMAIN_H

#include <QDialog>
#include "ui_DarwinMain.h"

#include "DUIObserver.h"

class DarwinMain : public QDialog, public DUIObserver
{
	Q_OBJECT

public:
	DarwinMain(QWidget *parent = 0, DUIHandler* handler = 0);
	~DarwinMain();
	void OnEvent(Message& ev) ;

private:
	Ui::DarwinMainClass ui;


private slots:
	void on_pushButtonStaffMgnt_clicked();
	void on_pushButtonLogoff_clicked();
};

#endif // DARWINMAIN_H
