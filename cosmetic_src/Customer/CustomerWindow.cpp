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
#include "CustomerLevelEditor.h"
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
	delete m_detailWidget;
	delete m_levelEditor;
	delete m_searchBox;
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
	case EVENT_CUSTOMERLEVEL:
		{
			m_customerLevelCache.clear();
			m_customerLevelNames->clear();
			m_customerLevelNames->insert(pair<uint32, string>(0, undefineStr));
			list<CustomerLevel>* data = 
				static_cast<list<CustomerLevel>*>(Msg.data());
			for(list<CustomerLevel>::iterator it = data->begin() ; 
				it != data->end() ; it++) {
				m_customerLevelCache[it->getId()] = *it;
				m_customerLevelNames->insert
					(pair<uint32, string>(it->getId(), it->getName()));
			}

			m_detailWidget->setCustomerLevels(data);
			if(NULL != m_levelEditor) {
				m_levelEditor->clearData();
				m_levelEditor->addCustomerLevel(data);
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
				m_detailWidget->browseCustomer
				(static_cast<Customer*>(Msg.data()));
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
					cmString, cmAddCustomerErrorStr);
			}
			break;
		}
	case	EVENT_REMOVECUSTOMER:
		{
			if(NULL != Msg.data()) {
				getAllCustomer();
			} else {
				MessageBox::showMessageBox
					(this, QMessageBox::Critical, cmString, removeError);
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
					cmString, cmModifyCustomerErrorStr);
			}
			break;
		}
	case	EVENT_CONSUMERECORDS:
		{
			break;
		}
	case	EVENT_SETCUSTOMERLEVEL:
		{
			list<CustomerLevel>* error = 
				static_cast<list<CustomerLevel>*>(Msg.data());
			getCustomerLevel();
			if(NULL!= error && !error->empty()){
				string errorstr = cmLevelStr;
				for(list<CustomerLevel>::iterator it = error->begin() ; 
					it != error->end() ; it++) {
					errorstr += leftMark;
					errorstr += it->getName();
					errorstr += rightMark;
				}
				errorstr += modifyWaring;
				MessageBox::showMessageBox
					(this, QMessageBox::Warning, cmString, errorstr);
			}
			delete error;
			break;
		}
	case	EVENT_REMOVECUSTOMERLEVEL:
		{
			list<CustomerLevel>* error = 
				static_cast<list<CustomerLevel>*>(Msg.data());
			getCustomerLevel();
			if(NULL!= error && !error->empty()){
				string errorstr = cmLevelStr;
				for(list<CustomerLevel>::iterator it = error->begin() ; 
					it != error->end() ; it++) {
					errorstr += leftMark;
					errorstr += it->getName();
					errorstr += rightMark;
				}
				errorstr += cmLevelRemoveWaring;
				MessageBox::showMessageBox
					(this, QMessageBox::Warning, cmString, errorstr);
			}
			delete error;
			break;
		}
	default: break;
	}
}

void CustomerWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		break;
	default:
		break;
	}
}

bool CustomerWindow::event(QEvent* ev){
	switch(ev->type()) {
		case QEvent::Show:
			{
				if(!m_started) {
					m_started = true;
					getCustomerLevel();
					getAllCustomer();
					showMaximized();
				}
				break;
			}
		case QEvent::ContextMenu:
			{
				QMenu mainMenu(this);
				mainMenu.addAction(ui.actionMenu);
				mainMenu.addAction(ui.actionLock);
				mainMenu.addAction(ui.actionLogOff);
				mainMenu.addAction(ui.actionExit);
				mainMenu.exec(dynamic_cast<QContextMenuEvent*>(ev)->globalPos());
				ev->accept();
				return true;
				break;
			}
	}
	return QMainWindow::event(ev);
}


bool CustomerWindow::eventFilter(QObject* obj, QEvent* ev){
	switch(ev->type()) {
		case QEvent::ContextMenu:
			{
				QMenu menu(this);
				if(ui.itemView == obj) {
					menu.addAction(ui.actionQuery);
					menu.addAction(ui.actionEdit);
					menu.addAction(ui.actionRemove);
				}
				if(ui.toolBar == obj || ui.menubar == obj) {
					menu.addAction(ui.actionSmallIcon);
					menu.addAction(ui.actionTextLabel);
					menu.addAction(ui.actionToolBar);
				}
				menu.exec(dynamic_cast<QContextMenuEvent*>(ev)->globalPos());
				ev->accept();
				return true;
				break;
			}
	}
	return QMainWindow::eventFilter(obj, ev);
}


void CustomerWindow::addCustomer(Customer* customer, QByteArray& image){
	Message* action = new Message(ACTION_ADDCUSTOMER, customer, &image);
	GetHandler()->StartAction(*action);
	delete action;
}

void CustomerWindow::viewItemActivated(int row, int column, QVariant & data){
	getCustomer(ui.itemView->sibling(row, 0).toUInt());
}

void CustomerWindow::addCustomer2View(list<Customer>* data)
{
	ui.itemView->clearData();
	list<Customer>::iterator it = data->begin();
	while(data->end() != it) {
		addCustomer2View(&(*it));
		it++;
	}
}

void CustomerWindow::addCustomer2View(Customer* data)
{
	ui.itemView->addCustomer(*data);	
}

void CustomerWindow::dealAction(QAction* action){
	if(action == ui.actionMenu) { Menu(); return; }
	if(action == ui.actionLogOff) { Logoff(); return; }
	if(action == ui.actionExit) { Exit(); return; }
	if(action == ui.actionRemove) { removeCustomer(); return; }
	if(action == ui.actionAdd) { addCustomer(); return; }
	if(action == ui.actionEdit) { editCustomer(); return; }
	if(action == ui.actionQuery) { TOBE_REALIZIED; return; }
	if(action == ui.actionLevelSetting) { levelSetting(); return; }
	if(action == ui.actionAboutCosmetic) { TOBE_REALIZIED; return; }
	if(action == ui.actionLock) { TOBE_REALIZIED; return; }
	if(action == ui.actionSmallIcon) { showSmallIcon(ui.actionSmallIcon->isChecked()); return; }
	if(action == ui.actionTextLabel) { showTextLabel(ui.actionTextLabel->isChecked()); return; }
	if(action == ui.actionToolBar) { showToolBar(ui.actionToolBar->isChecked()); return; }
}

void CustomerWindow::removeCustomer()	
{
	int row = 0;
	int col = 0;
	ui.itemView->currentIndex(row, col);
	uint32 currentID = ui.itemView->sibling(row, 0).toUInt();
	if(0 != currentID) {
		string  currentName = 
			string(ui.itemView->sibling(row, 2).toString().toLocal8Bit().data());
		QString confirm =LOCAL8BITSTR(cmRemoveCustomerConfirm).
			arg(LOCAL8BITSTR(currentName.c_str()));
		if(QMessageBox::No == MessageBox::
			showMessageBox(this, QMessageBox::Question, 
			cmString, confirm.toLocal8Bit().data()))
			return;
		removeCustomer(currentID);
	} else {
		MessageBox::showMessageBox
			(this, QMessageBox::Warning, cmString, zeroSelectionWarning);
	}
}

void CustomerWindow::editCustomer()
{
	int row = 0;
	int col = 0;
	ui.itemView->currentIndex(row, col);
	uint32 currentID = ui.itemView->sibling(row, 0).toUInt();
	if(0 != currentID) {
		ui.sideBar->showSideBar(true);
		m_detailWidget->editCustomer(NULL);
	} else {
		MessageBox::showMessageBox
			(this, QMessageBox::Warning, cmString, zeroSelectionWarning);
	}
}

void CustomerWindow::addCustomer()
{
	ui.sideBar->showSideBar(true);
	m_detailWidget->newCustomer();
}

void CustomerWindow::getAllCustomer(){
	Message* action = new Message(ACTION_GETALLCUSTOMER);
	GetHandler()->StartAction(*action);
	delete action;
}


void CustomerWindow::getCustomer(uint32 id){
	uint32* id1 = new uint32(id);
	uint32* id2 = new uint32(id);
	Message* action1 = new Message(ACTION_GETCUSTOMER, id1);
	GetHandler()->StartAction(*action1);
	delete action1;
	Message* action2 = new Message(ACTION_GETCUSTOMERPIC, id2);
	GetHandler()->StartAction(*action2);
	delete action2;
}


void CustomerWindow::getCustomerLevel(){
	Message* action = new Message(ACTION_GETCUSTOMERLEVEL);
	GetHandler()->StartAction(*action);
	delete action;
}


void CustomerWindow::modifyCustomer(Customer* customer, QByteArray& image){
	Message* action = new Message(ACTOIN_MODIFYCUSTOMER, customer, &image);
	GetHandler()->StartAction(*action);
	delete action;
}


void CustomerWindow::removeCustomer(uint32 id){
	uint32* id1 = new uint32(id);
	Message* action = new Message(ACTION_REMOVECUSTOMER, id1);
	GetHandler()->StartAction(*action);
	delete action;

}


void CustomerWindow::setCustomerLevel(void* data){
	Message* action = new Message(ACTION_SETCUSTOMERLEVEL, data);
	GetHandler()->StartAction(*action);
	delete action;

}

void CustomerWindow::Menu()
{
	Message* action = new Message(ACTION_MAINMENU);
	GetHandler()->StartAction(*action);
	delete action;
}

void CustomerWindow::Logoff()
{
	Message* action = new Message(ACTION_LOGOFF);
	GetHandler()->StartAction(*action);
	delete action;
}

void CustomerWindow::Exit()
{
	Message* action = new Message(ACTION_EXIT);
	GetHandler()->StartAction(*action);
	delete action;
}

void CustomerWindow::showSmallIcon(bool flag)
{
	if(flag) {
		ui.toolBar->setIconSize(QSize(32, 32));
	} else {
		ui.toolBar->setIconSize(QSize(48, 48));
	}
}

void CustomerWindow::showTextLabel(bool flag)
{
	if(flag) {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	} else {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	}
}

void CustomerWindow::showToolBar(bool flag)
{
	if(flag) {
		ui.toolBar->show();
	} else {
		ui.toolBar->close();
	}
}

void CustomerWindow::levelSetting()
{
	m_levelEditor = new CustomerLevelEditor(this);
	m_levelEditor->setWindowModality(Qt::WindowModal);
	m_levelEditor->setWindowFlags(Qt::Tool);
	connect(m_levelEditor, SIGNAL(submitted(void*)), 
		this, SLOT(setCustomerLevel(void*)));
	m_levelEditor->changeMode(ItemEditor::EditMode);
	for(CustomerLevelArray::const_iterator it = m_customerLevelCache.begin() ; 
		m_customerLevelCache.end() != it ; it++)
		m_levelEditor->addCustomerLevel(it->second);
	m_levelEditor->show();
}

void CustomerWindow::submitCustomer
(Customer* data, QByteArray& picData, uint32 mode)
{
	if(CustomerDetailWidget::CUSTOMER_NEW == mode)// || 0 == data->id())
		addCustomer(data, picData);
	if(CustomerDetailWidget::CUSTOMER_MODIFY == mode)// && 0 != data->id())
		modifyCustomer(data, picData);
}