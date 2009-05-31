#include "CustomerWindow.h"
#include <QByteArray>
#include <QEvent>
#include <QPoint>
#include <QContextMenuEvent>
#include "DUIHandler.h"
#include "common.h"
#include "AnythingFactory.h"
#include "Singleton.h"
#include "Message.h"
#include "messagedef.h"
#include "SearchBox.h"
#include "CustomerDetailWidget.h"
//#include "CustomerLevelEditor.h"
#include "UiStrings.h"
#include "MessageBox.h"

CustomerWindow::CustomerWindow(QWidget *parent)
:QMainWindow(parent),m_started(false),m_levelEditor(NULL)
{
	m_customerLevelNames = AnythingFactory<ArrayUint32String>::
		instance()->createAnything(CUSTOMERLEVEL);	

	ui.setupUi(this);
	ui.itemView->installEventFilter(this);
	ui.menubar->installEventFilter(this);
	ui.toolBar->installEventFilter(this);

	m_searchBox = new SearchBox(this);
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmIdStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmNameStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmSexStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmLevelStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmCellStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmPhoneStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmAddressStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmDescriptionStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmDescriptionStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(cmDepositStr));


	m_detailWidget = new CustomerDetailWidget(this);
	ui.sideBar->addWidget(m_detailWidget, 0, 0);
	ui.sideBar->addWidget(m_searchBox, 1, 0);

	connect(m_searchBox, SIGNAL(regExpChanged(QRegExp &)), 
		ui.itemView, SLOT(changeRegExp(QRegExp &)));
	connect(m_searchBox, SIGNAL(columnChanged(int)), 
		ui.itemView, SLOT(changeFilterColumn(int)));
	connect(m_searchBox, SIGNAL(sortChanged(int)), 
		ui.itemView, SLOT(changeSortCase(int)));
	connect(m_detailWidget, SIGNAL(submittedCustomer(Customer*, QByteArray&, uint32)), 
		this, SLOT(submitCustomer(Customer*, QByteArray&, uint32)));
	connect(ui.itemView, SIGNAL(itemActivated(int, int, QVariant &)), 
		this, SLOT(viewItemActivated(int, int, QVariant &)));

}

CustomerWindow::~CustomerWindow()
{

}


void CustomerWindow::OnEvent(Message& Msg){
	switch(Msg.type())
	{
	case EVENT_CUSTOMERMGNT:
		{
			if(!isVisible())
				show();
			else
				activateWindow();
			break;
		}
	case EVENT_LOGGEDOFF:
		{
			close();
			break;
		}
	case EVENT_EXIT:
		{
			close();
			break;
		}
		/*
	case EVENT_CUSTOMERLEVEL:
		{
			m_customerLevelCache.clear();
			m_customerLevelNames->clear();
			m_customerLevelNames->insert(pair<uint32, string>(0, undefineStr));
			list<CustomerLevel>* data = static_cast<list<CustomerLevel>*>(Msg.data());
			for(list<CustomerLevel>::iterator it = data->begin() ; it != data->end() ; it++) {
				m_customerLevelCache[it->getId()] = *it;
				m_customerLevelNames->insert(pair<uint32, string>(it->getId(), it->getName()));
			}

			m_detailWidget->setCustomerLevels(data);
			if(NULL != m_typeEditor) {
				m_typeEditor->clearData();
				m_typeEditor->addCustomerLevel(data);
			}
			break;
		}
	case	EVENT_ALLCUSTOMERS:
		{
			addCustomer2View(static_cast<list<Customer>*>(Msg.data()));
			break;
		}
	case	EVENT_CUSTOMER:
		{
			if(NULL != Msg.data())
				m_detailWidget->browseCustomer(static_cast<Customer*>(Msg.data()));
			break;
		}
	case	EVENT_CUSTOMERPIC:
		{
			if(NULL != Msg.data()) {
				QByteArray* image = static_cast<QByteArray*>(Msg.data());
				m_detailWidget->displayPicture(*image);
				image->clear();
				delete image;
			} else {
				m_detailWidget->clearPicture();
			}
			break;
		}
	case	EVENT_ADDCUSTOMER:
		{
			if(NULL != Msg.data()) {
				Customer* data = static_cast<Customer*>(Msg.data());
				addCustomer2View(data);
				m_detailWidget->browseCustomer(data);
				if(NULL != Msg.data2()) {
					QByteArray* image = static_cast<QByteArray*>(Msg.data2());
					m_detailWidget->displayPicture(*image);
					delete image;
				}
			} else {
				MessageBox::showMessageBox(this, QMessageBox::Critical, 
					bmString, bmAddCustomerErrorStr);
			}
			break;
		}
	case	EVENT_REMOVECUSTOMER:
		{
			if(NULL != Msg.data()) {
				//					m_detailWidget->clearPicture();
				//					m_detailWidget->clearData();
				getAllCustomer();
			} else {
				MessageBox::showMessageBox(this, QMessageBox::Critical, bmString, removeError);
			}
			break;
		}
	case	EVENT_MODIFYCUSTOMER:
		{
			if(NULL != Msg.data()) {
				Customer* data = static_cast<Customer*>(Msg.data());
				m_detailWidget->browseCustomer(data);
				if(NULL != Msg.data2()) {
					QByteArray* image = static_cast<QByteArray*>(Msg.data2());
					m_detailWidget->displayPicture(*image);
					delete image;
				}
				getAllCustomer();
			} else {
				MessageBox::showMessageBox(this, QMessageBox::Critical, 
					bmString, bmModifyCustomerErrorStr);
			}
			break;
		}
	case	EVENT_CUSTOMERRECORD:
		{
			break;
		}
	case	EVENT_SETCUSTOMERTYPE:
		{
			list<CustomerLevel>* error = static_cast<list<CustomerLevel>*>(Msg.data());
			getCustomerLevel();
			if(NULL!= error && !error->empty()){
				string errorstr = bmTypeStr;
				for(list<CustomerLevel>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += leftMark;
					errorstr += it->getName();
					errorstr += rightMark;
				}
				errorstr += modifyWaring;
				MessageBox::showMessageBox(this, QMessageBox::Warning, bmString, errorstr);
			}
			delete error;
			break;
		}
	case	EVENT_REMOVECUSTOMERTYPE:
		{
			list<CustomerLevel>* error = static_cast<list<CustomerLevel>*>(Msg.data());
			getCustomerLevel();
			if(NULL!= error && !error->empty()){
				string errorstr = bmTypeStr;
				for(list<CustomerLevel>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += leftMark;
					errorstr += it->getName();
					errorstr += rightMark;
				}
				errorstr += bmTypeRemoveWaring;
				MessageBox::showMessageBox(this, QMessageBox::Warning, bmString, errorstr);
			}
			delete error;
			break;
		}
		*/
	default: break;
	}
}