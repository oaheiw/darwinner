#ifndef CUSTOMERDETAILWIDGET_H
#define CUSTOMERDETAILWIDGET_H

#include <QWidget>
#include "ui_CustomerDetailWidget.h"

class CustomerDetailWidget : public QWidget
{
	Q_OBJECT

public:
	CustomerDetailWidget(QWidget *parent = 0);
	~CustomerDetailWidget();

private:
	Ui::CustomerDetailWidgetClass ui;
};

#endif // CUSTOMERDETAILWIDGET_H
