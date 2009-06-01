#ifndef BUSINESSWINDOW_H
#define BUSINESSWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_BusinessWindow.h"
#include "DUIObserver.h"
#include "Business.h"
#include "BusinessType.h"
#include "common.h"
#include <list>
#include <map>
class SearchBox;
class BusinessDetailWidget;
class BusinessTypeEditor;
class QByteArray;
class QEvent;
using namespace std;

typedef map<uint32, BusinessType> BusinessTypeArray;

class BusinessWindow : public QMainWindow, public DUIObserver
{
    Q_OBJECT
    Q_DISABLE_COPY(BusinessWindow)
public:
    BusinessWindow(QWidget *parent = 0);
    ~BusinessWindow();
	bool event(QEvent* ev);
	void OnEvent(Message& Msg);

protected:
    virtual void changeEvent(QEvent *e);
	virtual bool eventFilter(QObject* obj, QEvent* ev);

	private slots:
	void submitBusiness(Business* data, QByteArray& picData, uint32 mode);
	void dealAction(QAction* action);
	void viewItemActivated(int row, int column, QVariant & data);
	void addBusiness(Business* business, QByteArray& image);
	void modifyBusiness(Business* business, QByteArray& image);
	void setBusinessType(void* data);

private:
	Ui::BusinessWindowClass ui;
	void addBusiness2View(list<Business>* data);
	void addBusiness2View(Business* data);
	void getAllBusiness();
	void getBusiness(uint32 id);
	void getBusinessType();
	void removeBusiness(uint32 id);
	void Exit();
	void Logoff();
	void Menu();
	void addBusiness();
	void removeBusiness();
	void editBusiness();
	void showSmallIcon(bool flag);
	void showTextLabel(bool flag);
	void showToolBar(bool flag);
	void typeSetting();

	SearchBox*  m_searchBox;
	BusinessDetailWidget* m_detailWidget;
	BusinessTypeArray m_businessTypeCache;
	BusinessTypeEditor* m_typeEditor;
	bool m_started;
	ArrayUint32String* m_businessTypeNames;
};

#endif // BUSINESSWINDOW_H
