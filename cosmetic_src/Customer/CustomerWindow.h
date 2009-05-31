#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QMainWindow>
#include "ui_CustomerWindow.h"
#include "DUIObserver.h"
#include "Customer.h"
#include "CustomerLevel.h"
#include "common.h"
#include <list>
#include <map>
class SearchBox;
class CustomerDetailWidget;
class CustomerLevelEditor;
class QByteArray;
class QEvent;
using namespace std;

typedef map<uint32, CustomerLevel> CustomerLevelArray;

class CustomerWindow : public QMainWindow, public DUIObserver
{
	Q_OBJECT

public:
	CustomerWindow(QWidget *parent = 0);
	~CustomerWindow();
//	bool event(QEvent* ev);
	void OnEvent(Message& Msg);

protected:
//	virtual void changeEvent(QEvent *e);
//	virtual bool eventFilter(QObject* obj, QEvent* ev);

private:
	Ui::CustomerWindowClass ui;
/*	void addCustomer2View(list<Customer>* data);
	void addCustomer2View(Customer* data);
	void getAllCustomer();
	void getCustomer(uint32 id);
	void getCustomerType();
	void removeCustomer(uint32 id);
	void Exit();
	void Logoff();
	void Menu();
	void addCustomer();
	void removeCustomer();
	void editCustomer();
	void showSmallIcon(bool flag);
	void showTextLabel(bool flag);
	void showToolBar(bool flag);
	void levelSetting();
*/
	SearchBox* m_searchBox;
	CustomerDetailWidget* m_detailWidget;
	CustomerLevelArray m_customerLevelCache;
	CustomerLevelEditor* m_levelEditor;
	bool m_started;
	ArrayUint32String* m_customerLevelNames;

private slots:
/*	void submitCustomer(Customer* data, QByteArray& picData, uint32 mode);
	void dealAction(QAction* action);
	void viewItemActivated(int row, int column, QVariant & data);
	void addCustomer(Customer* customer, QByteArray& image);
	void modifyCustomer(Customer* customer, QByteArray& image);
	void setCustomerLevels(void* data);
*/
};

#endif // CUSTOMERWINDOW_H
