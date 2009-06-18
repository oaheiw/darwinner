#include "StockSetting.h"

StockSetting::StockSetting(short warningValue, short tipDate, QWidget *parent)
: QWidget(parent, Qt::Tool),m_warningValue(warningValue),m_tipDate(tipDate)
{
	ui.setupUi(this);
	ui.warningSpinBox->setValue(m_warningValue);
	ui.dateBox->setValue(m_tipDate);
	if(NULL != parent) {
		move(parent->pos().x() + parent->width()/2 - width()/2, 
			parent->pos().y() + parent->height()/2 - height()/2);
	}
}

StockSetting::~StockSetting()
{

}

void StockSetting::submitSetting()
{
	m_warningValue = ui.warningSpinBox->value();
	m_tipDate = ui.dateBox->value();
	emit settingsSubmitted(m_warningValue, m_tipDate);
}