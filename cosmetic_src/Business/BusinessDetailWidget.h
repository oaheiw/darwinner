#ifndef BUSINESSDETAILWIDGET_H
#define BUSINESSDETAILWIDGET_H

#include <QWidget>
#include "ui_BusinessDetailWidget.h"

class BusinessDetailWidget : public QWidget
{
	Q_OBJECT

public:
	BusinessDetailWidget(QWidget *parent = 0);
	~BusinessDetailWidget();

private:
	Ui::BusinessDetailWidgetClass ui;
};

#endif // BUSINESSDETAILWIDGET_H
