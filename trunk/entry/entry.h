#ifndef ENTRY_H
#define ENTRY_H

#include <QtGui/QDialog>
#include "ui_entry.h"


class entry : public QDialog
{
	Q_OBJECT

public:
	entry(QWidget *parent = 0, Qt::WFlags flags = 0);
	~entry();
	Ui::entryClass ui;


private slots:
	void on_pushButtonLogin_clicked();
};

#endif // ENTRY_H
