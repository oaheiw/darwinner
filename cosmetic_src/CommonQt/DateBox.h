#ifndef DATEBOX_H
#define DATEBOX_H

#include <QWidget>
#include "ui_DateBox.h"
#include <QDate>
class QCalendarWidget;
class QEvent;


class DateBox : public QWidget
{
	Q_OBJECT

public:
	DateBox(QWidget *parent = 0);
	~DateBox();
	bool event(QEvent * ev);

	enum INIT_MODE {
		INIT_FROM,
		INIT_TO
	};

signals:
	void dateRangeChange(QDate& from, QDate& to);

private:
	void showCalendar();
	void closeCalendar();
	QCalendarWidget* initCalendar(INIT_MODE mode);
	QDate m_from;
	QDate m_to;
	QCalendarWidget* m_calendarFrom;
	QCalendarWidget* m_calendarTo;
	Ui::DateBoxClass ui;

private slots:
	void fromCalendarChanged(const QDate&);
	void toCalendarChanged(const QDate&);
	void fromDateChanged(QDate);
	void toDateChanged(QDate);
	void fromButtonToggled(bool);
	void toButtonToggled(bool);

public slots:
	void moveCalendar();
};

#endif // DATEBOX_H
