#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QMainWindow>
#include "DUIObserver.h"
#include "ui_StockWindow.h"
class Message;

class StockWindow : public QMainWindow, public DUIObserver
{
	Q_OBJECT

public:
	StockWindow(QWidget *parent = 0);
	~StockWindow();
	bool event(QEvent* ev);
	void OnEvent(Message& Msg);

protected:
	virtual void changeEvent(QEvent *e);
	virtual bool eventFilter(QObject* obj, QEvent* ev);

private:
	bool m_started;
	Ui::StockWindowClass ui;
};

#endif // STOCKWINDOW_H
