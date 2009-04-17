#ifndef JOBTYPE_H
#define JOBTYPE_H

class QAbstractItemModel;
#include <QWidget>
#include "ui_job.h"
#include "Job.h"
#include <list>
using namespace std;
class QFont;

class JobTypeWidget : public QWidget
{
	Q_OBJECT

public:
	JobTypeWidget(QWidget *parent = 0, int mode = 0);
	~JobTypeWidget();
	void settingFont(QFont& font);
	list<Job>* getJobList();

private:
	Ui::Job ui;
	QAbstractItemModel* m_DataModel;
	int m_mode;

private slots:
	void add();
	void remove();
	void submit();
};

#endif // JOBTYPE_H
