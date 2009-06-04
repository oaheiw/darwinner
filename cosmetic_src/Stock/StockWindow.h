#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QMainWindow>
#include "ui_StockWindow.h"

class StockWindow : public QMainWindow
{
	Q_OBJECT

public:
	StockWindow(QWidget *parent = 0);
	~StockWindow();

private:
	Ui::StockWindowClass ui;
};

#endif // STOCKWINDOW_H
