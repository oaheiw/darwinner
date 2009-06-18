#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QMainWindow>
#include "DUIObserver.h"
#include "common.h"
#include "ui_StockWindow.h"
class Stock;
class Inventory;
class Message;
class Business;
class StockSetting;

class StockWindow : public QMainWindow, public DUIObserver
{
	Q_OBJECT

public:
	StockWindow(QWidget *parent = 0);
	~StockWindow();
	virtual bool event(QEvent* ev);
	virtual void OnEvent(Message& Msg);

protected:
	virtual void changeEvent(QEvent *e);
	virtual bool eventFilter(QObject* obj, QEvent* ev);

private:
	bool m_started;
	StockSetting* m_settingPage;
	Ui::StockWindowClass ui;

	void getAllCommodities();
	void addCommodity2View(list<Business>* data);
	void getStock(uint32 id);
	void addStock2View(list<Stock>* data);
	void getInventory(uint32 id);
	void addInventory2View(list<Inventory>* data);
	void stockSetting();
	void newStock(STOCKING_DIRECTION direction);
	void newInventory();
	void newBatchInventory();

	void Exit();
	void Logoff();
	void Menu();
	void showSmallIcon(bool flag);
	void showTextLabel(bool flag);
	void showToolBar(bool flag);

private slots:
	void dealAction(QAction* action);
	void viewItemActivated(int row, int column, QVariant & data);
	void submitStock(Stock* data);
	void submitInventory(Inventory* data);
	void submitWarningLevel(uint32 value);
	void submitCheckDate(short date);
	void submitSettings(uint32 value, short date);
};

#endif // STOCKWINDOW_H
