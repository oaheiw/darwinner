#ifndef STAFFCONFIGURATION_H
#define STAFFCONFIGURATION_H

#include <QDialog>
#include "ui_staffconfiguration.h"

class StaffConfiguration : public QDialog
{
	Q_OBJECT

public:
	StaffConfiguration(QWidget *parent = 0);
	~StaffConfiguration();

private:
	Ui::StaffConfigurationClass ui;
};

#endif // STAFFCONFIGURATION_H
