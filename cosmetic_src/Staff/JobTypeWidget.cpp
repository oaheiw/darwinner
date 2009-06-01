#include <QtGui>
#include "JobTypeWidget.h"
#include <QAbstractItemModel>
#include "SpinBoxDelegate.h"
#include "UiStrings.h"
#include <limits>
using namespace std;

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
		ui.submitPushButton->hide();
	} 

	m_DataModel = new QStandardItemModel(0, 5, this);
	ui.jobTableView->setModel(m_DataModel);
	ui.jobTableView->setAlternatingRowColors(true);
	ui.jobTableView->hideColumn(0);
	ui.jobTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_DataModel->setHeaderData(col, Qt::Horizontal, LOCAL8BITSTR(idStr));
	ui.jobTableView->setColumnWidth(col++, 40);
	m_DataModel->setHeaderData(col, Qt::Horizontal, LOCAL8BITSTR(staffJobStr));
	ui.jobTableView->setColumnWidth(col++, 70);
	m_DataModel->setHeaderData(col, Qt::Horizontal, LOCAL8BITSTR(staffProfitStr));
	ui.jobTableView->setColumnWidth(col++, 60);
	m_DataModel->setHeaderData(col, Qt::Horizontal, LOCAL8BITSTR(staffJobSalaryStr));
	ui.jobTableView->setColumnWidth(col++, 60);
	m_DataModel->setHeaderData(col++, Qt::Horizontal, LOCAL8BITSTR(staffDescriptionStr));

	SpinBoxDelegate *delegateProfit = new SpinBoxDelegate(ui.jobTableView);
	delegateProfit->setRange(0, 100);
	delegateProfit->setSuffix(percentStr);
	ui.jobTableView->setItemDelegateForColumn (2, delegateProfit);

	SpinBoxDelegate *delegateSalary = new SpinBoxDelegate(ui.jobTableView);
	delegateSalary->setRange(0, numeric_limits<int>::max());
	delegateSalary->setPrefix(moneyStr);
	ui.jobTableView->setItemDelegateForColumn (3, delegateSalary);
	
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
	/*
	m_DataModel->setData(m_DataModel->index(row, 0), 0);
	m_DataModel->setData(m_DataModel->index(row, 1), "");
	m_DataModel->setData(m_DataModel->index(row, 2), 0);
	m_DataModel->setData(m_DataModel->index(row, 3), 0);
	m_DataModel->setData(m_DataModel->index(row, 4), "");
	*/

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
		tempJob.setBaseSalary(data.data().toUInt());
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
		int row = m_DataModel->rowCount();
		m_DataModel->insertRow(row);
		ui.jobTableView->setRowHeight(row, 20);

		m_DataModel->setData(m_DataModel->index(row, 0), it->id());
		m_DataModel->setData(m_DataModel->index(row, 1), LOCAL8BITSTR(it->name().c_str()));
		m_DataModel->setData(m_DataModel->index(row, 2), it->profit());
		m_DataModel->setData(m_DataModel->index(row, 3), it->baseSalary());
		m_DataModel->setData(m_DataModel->index(row, 4), LOCAL8BITSTR(it->description().c_str()));
	}
}

