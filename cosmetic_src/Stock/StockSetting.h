#ifndef STOCKSETTING_H
#define STOCKSETTING_H

#include <QWidget>
#include "ui_StockSetting.h"
#include "common.h"

class StockSetting : public QWidget
{
	Q_OBJECT

public:
	StockSetting(short warningValue, short tipDate, QWidget *parent = 0);
	~StockSetting();

signals:
	void settingsSubmitted(uint32 warningValue, short tipDate);

private:
	uint32 m_warningValue;
	short m_tipDate;
	Ui::StockSettingClass ui;

private slots:
	void submitSetting();
};

#endif // STOCKSETTING_H
