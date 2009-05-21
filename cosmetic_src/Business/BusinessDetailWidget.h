#ifndef BUSINESSDETAILWIDGET_H
#define BUSINESSDETAILWIDGET_H

#include <QWidget>
#include "ui_BusinessDetailWidget.h"
#include "common.h"
#include <list>
using namespace std;
class Business;
class QByteArray;
class BusinessType;


class BusinessDetailWidget : public QWidget
{
	Q_OBJECT

public:
	enum MODE {
		BUSINESS_BROWSE = 0,
		BUSINESS_MODIFY,
		BUSINESS_NEW,
		SINFO_END
	};

	BusinessDetailWidget(QWidget *parent = 0, uint32 mode = BUSINESS_BROWSE);
	~BusinessDetailWidget();
	void browseBusiness(Business* data);
	void clearData();
	void displayPicture(QByteArray& data);
	void clearPicture();
	void editBusiness(Business* data);
	void newBusiness();
	void setBusinessTypes(list<BusinessType>* types);

signals:
	void submittedBusiness(Business* data, QByteArray& picData, uint32 mode);

private:
	Ui::BusinessDetailWidgetClass ui;
	QByteArray m_businessPicData;
	uint32 m_mode;
	QPixmap m_zeroPicture;
	void changeMode(uint32 mode);


private slots:
	void selectPicture();
	void submit();
};

#endif // BUSINESSDETAILWIDGET_H
