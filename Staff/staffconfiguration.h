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
	Ui::StaffConfigurationClass ui;

public slots:
     void changePage(QListWidgetItem *current, QListWidgetItem *previous);


signals:
	void jobSubmitted(list<Job>* jobList);
	void levelSubmitted(list<Level>* levelList);
	void removeJob(Job* job);
	void removeLevel(Level* level);

private:
	void createIcons();
};

#endif // STAFFCONFIGURATION_H
