#include "ProgressWidget.h"

ProgressWidget::ProgressWidget(QString& text, int min, int max, QWidget *parent)
:QWidget(parent, Qt::Popup)
{
	ui.setupUi(this);
	setText(text);
	setRange(min, max);
	setValue(0);
}

ProgressWidget::~ProgressWidget()
{

}

void ProgressWidget::setText(QString & text)
{
	ui.infoLabel->setText(text);
}

void ProgressWidget::setValue(int progress)
{
	ui.progressBar->setValue(progress);
}

void ProgressWidget::setRange(int min, int max)
{
	ui.progressBar->setRange(min, max);
}