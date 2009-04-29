#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>
#include "ui_ProgressWidget.h"

class ProgressWidget : public QWidget
{
	Q_OBJECT

public:
	ProgressWidget(QString& text, int min, int max, QWidget *parent = 0);
	void setText(QString& text);
	void setValue(int progress);
	void setRange(int min, int max);
	~ProgressWidget();

private:
	Ui::ProgressWidgetClass ui;
};

#endif // PROGRESSWIDGET_H
