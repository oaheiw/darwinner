#include "DateBox.h"
#include <QCalendarWidget>
 #include <QDateTime>
#include <QEvent>

DateBox::DateBox(QWidget *parent)
:QWidget(parent)
{
	ui.setupUi(this);
	m_to = QDateTime::currentDateTime().date();
	m_from = m_to.addMonths(-1);
	ui.fromDate->setDate(m_from);
	ui.toDate->setDate(m_to);
//	m_calendarFrom = NULL;
//	m_calendarTo = NULL;
}

DateBox::~DateBox()
{

}

void DateBox::fromDateChanged(QDate date)
{
	if(date <= m_to) {
		m_from = date;
	} else {
		m_from = ui.toDate->date();
		ui.fromDate->setDate(m_from);
	}
	emit dateRangeChange(m_from, m_to);
}

void DateBox::toDateChanged(QDate date)
{
	if(date >= m_from) {
		m_to = date;
	} else {
		m_to = ui.fromDate->date();
		ui.toDate->setDate(m_to);
	}
	emit dateRangeChange(m_from, m_to);
}
/*
void DateBox::fromButtonToggled(bool toggled)
{
	if(toggled) {
		if(NULL == m_calendarFrom) {
			m_calendarFrom = initCalendar(INIT_FROM);
		} else { ; }
		ui.toToolButton->setDisabled(true);
		m_calendarFrom->setMaximumDate(m_to);
		m_calendarFrom->show();
		moveCalendar();
	} else {
		m_calendarFrom->close();
		ui.toToolButton->setDisabled(false);
	}
}

void DateBox::toButtonToggled(bool toggled)
{
	if(toggled) {
		if(NULL == m_calendarTo) {
			m_calendarTo = initCalendar(INIT_TO);
		} else { ; }
		ui.fromToolButton->setDisabled(true);
		m_calendarTo->setDateRange(m_from, QDateTime::currentDateTime().date());
		m_calendarTo->show();
		moveCalendar();
	} else {
		m_calendarTo->close();
		ui.fromToolButton->setDisabled(false);
	}
}

QCalendarWidget* DateBox::initCalendar(INIT_MODE mode)
{
	QCalendarWidget* calendar = new QCalendarWidget(dynamic_cast<QWidget*>(parent()));
	calendar->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	calendar->setLocale(QLocale(QLocale::Chinese, QLocale::HongKong));
	calendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
	calendar->setSelectionMode(QCalendarWidget::SingleSelection);
	calendar->setGridVisible(true);
	calendar->setFixedSize(150, 150);
	if(INIT_TO == mode) {
		calendar->setDateRange(m_from, QDateTime::currentDateTime().date());
		connect(calendar, SIGNAL(activated(const QDate &)), this, SLOT(toCalendarChanged(const QDate&)));
		connect(calendar, SIGNAL(clicked(const QDate &)), this, SLOT(toCalendarChanged(const QDate&)));
	} else {;}
	if(INIT_FROM == mode) {
		calendar->setMaximumDate(m_to);
		connect(calendar, SIGNAL(activated(const QDate &)), this, SLOT(fromCalendarChanged(const QDate &)));
		connect(calendar, SIGNAL(clicked(const QDate &)), this, SLOT(fromCalendarChanged(const QDate&)));
	} else {;}
	return calendar;
}

void DateBox::fromCalendarChanged(const QDate& date)
{
	ui.fromDate->setDate(date);
}

void DateBox::toCalendarChanged(const QDate& date)
{
	ui.toDate->setDate(date);
}

void DateBox::moveCalendar()
{
	if(NULL != m_calendarFrom && m_calendarFrom->isVisible()) {
		QPoint global = mapToGlobal(ui.fromDate->pos());
		m_calendarFrom->move(global.x(), global.y()+ui.fromDate->height());
	} else { ; }
	if(NULL != m_calendarTo && m_calendarTo->isVisible()) {
		QPoint global = mapToGlobal(ui.toDate->pos());
		m_calendarTo->move(global.x(), global.y()+ui.toDate->height());
	} else { ; }
}

void DateBox::showCalendar()
{
	if(NULL != m_calendarFrom && ui.fromToolButton->isChecked()) {
		m_calendarFrom->show();
	} else { ; }
	if(NULL != m_calendarTo && ui.toToolButton->isChecked()) {
		m_calendarTo->show();
	} else { ; }
	moveCalendar();
}

void DateBox::closeCalendar()
{
	if(NULL != m_calendarFrom && m_calendarFrom->isVisible()) {
		m_calendarFrom->close();
	} else { ; }
	if(NULL != m_calendarTo && m_calendarTo->isVisible()) {
		m_calendarTo->close();
	} else { ; }
}

bool DateBox::event(QEvent * ev)
{
	switch(ev->type()) {
		case QEvent::Close:
		case QEvent::Hide:
		{
			closeCalendar();
			break;
		}
		case QEvent::Show:
		{
			showCalendar();
			break;
		}
	}
	return QWidget::event(ev);
}
*/