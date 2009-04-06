#ifndef DARWINMAIN_H
#define DARWINMAIN_H

#include <QDialog>
#include "ui_DarwinMain.h"

class DarwinMain : public QDialog
{
	Q_OBJECT

public:
	DarwinMain(QWidget *parent = 0);
	~DarwinMain();
	Ui::DarwinMainClass ui;


private slots:
	void on_pushButtonStuffMgnt_clicked();
	void on_pushButtonLogoff_clicked();
};

#endif // DARWINMAIN_H
