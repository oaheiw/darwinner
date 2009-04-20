#include <QtGui>
#include "JobTypeWidget.h"
#include <QAbstractItemModel>

JobTypeWidget::JobTypeWidget(QWidget *parent, int mode)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.addPushButton->setDefault(true);
	QFont font = QFont("SimSun", 9);
	settingFont(font);
	int col = 0;
	m_mode = mode;

	if(0 == mode) {
		ui.submitPushButton->setDisabled(true);
	} 

	m_DataModel = new QStandardItemModel(0, 4, this);
	ui.jobTableView->setModel(m_DataModel);
	ui.jobTableView->setAlternatingRowColors(true);
	ui.jobTableView->hideColumn(0);
	ui.jobTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_DataModel->setHeaderData(col, Qt::Horizontal, QString::fromLocal8Bit("编号"));
	ui.jobTableView->setColumnWidth(col++, 40);
	m_DataModel->setHeaderData(col, Qt::Horizontal, QString::fromLocal8Bit("职务"));
	ui.jobTableView->setColumnWidth(col++, 60);
	m_DataModel->setHeaderData(col, Qt::Horizontal, QString::fromLocal8Bit("提成(%)"));
	ui.jobTableView->setColumnWidth(col++, 65);
	m_DataModel->setHeaderData(col++, Qt::Horizontal, QString::fromLocal8Bit("备注"));


	connect(ui.addPushButton, SIGNAL(clicked()), this, SLOT(add()));
	connect(ui.removePushButton, SIGNAL(clicked()), this, SLOT(remove()));
	connect(ui.submitPushButton, SIGNAL(clicked()), this, SLOT(submit()));
}

JobTypeWidget::~JobTypeWidget()
{

}

void JobTypeWidget::settingFont(QFont& font)
{
	font.setBold(true);
	ui.jobTableView->horizontalHeader()->setFont(font);
	ui.jobTableView->verticalHeader()->setFont(font);
	font.setBold(false);
	ui.addPushButton->setFont(font);
	ui.removePushButton->setFont(font);
	ui.submitPushButton->setFont(font);
	ui.jobTableView->setFont(font);
}

void JobTypeWidget::add()
{
	int row = m_DataModel->rowCount();
	m_DataModel->insertRow(row);
	ui.jobTableView->setRowHeight(row, 20);
	m_DataModel->setData(m_DataModel->index(row, 0), 0);
	m_DataModel->setData(m_DataModel->index(row, 1), "");
	m_DataModel->setData(m_DataModel->index(row, 2), 0);
	m_DataModel->setData(m_DataModel->index(row, 3), "");

}
void JobTypeWidget::remove()
{
	int row = ui.jobTableView->currentIndex().row();
	m_DataModel->removeRow(row);
}
void JobTypeWidget::submit()
{
	emit submitted(getJobList());
}

list<Job>* JobTypeWidget::getJobList()
{	
	list<Job>* jobList = new list<Job>;
	for (int row=0; row < m_DataModel->rowCount(); row++)
	{	
		Job tempJob;
		int col=0;
		QModelIndex data;
		data = m_DataModel->index(row, col++);
		tempJob.setId(data.data().toUInt());
		data = m_DataModel->index(row, col++);
		if(data.data().toString().isEmpty()) continue;// ignore job with empty name
		tempJob.setName(data.data().toString().toLocal8Bit().data());
		data = m_DataModel->index(row, col++);
		tempJob.setProfit(data.data().toUInt());
		data = m_DataModel->index(row, col++);
		tempJob.setDescription(data.data().toString().toLocal8Bit().data());
		jobList->push_back(tempJob);
	}
	return jobList;
}

void JobTypeWidget::pushjobs(list<Job>* jobs)
{
	m_DataModel->removeRows(0, m_DataModel->rowCount());
	for(list<Job>::iterator it=jobs->begin() ; jobs->end()!=it ; it++) {
		m_DataModel->insertRow(0);
		ui.jobTableView->setRowHeight(0, 20);

		m_DataModel->setData(m_DataModel->index(0, 0), it->id());
		m_DataModel->setData(m_DataModel->index(0, 1), QString::fromLocal8Bit(it->name().c_str()));
		m_DataModel->setData(m_DataModel->index(0, 2), it->profit());
		m_DataModel->setData(m_DataModel->index(0, 3), QString::fromLocal8Bit(it->description().c_str()));
	}
}