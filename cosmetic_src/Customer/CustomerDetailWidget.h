#ifndef CUSTOMERDETAILWIDGET_H
#define CUSTOMERDETAILWIDGET_H

#include <QWidget>
#include "ui_CustomerDetailWidget.h"
#include "common.h"
#include <list>
using namespace std;
class Customer;
class QByteArray;
class CustomerLevel;
class QAbstractItemModel;

class CustomerDetailWidget : public QWidget
{
	Q_OBJECT

public:
	enum MODE {
		CUSTOMER_BROWSE = 0,
		CUSTOMER_MODIFY,
		CUSTOMER_NEW,
		SINFO_END
	};
	CustomerDetailWidget(QWidget *parent = 0, uint32 mode = CUSTOMER_BROWSE);
	~CustomerDetailWidget();

	void browseCustomer(Customer* data);
	void clearData();
	void displayPicture(QByteArray& data);
	void clearPicture();
	void editCustomer(Customer* data);
	void newCustomer();
	void setCustomerLevels(list<CustomerLevel>* data);

signals:
	void submittedCustomer(Customer* data, QByteArray& picData, uint32 mode);

private:
	Ui::CustomerDetailWidgetClass ui;
	QByteArray m_customerPicData;
	QAbstractItemModel* m_dataModel;
	uint32 m_mode;
	QPixmap m_zeroPicture;
	void changeMode(uint32 mode);


private slots:
	void selectPicture();
	void submit();

};

#endif // CUSTOMERDETAILWIDGET_H
