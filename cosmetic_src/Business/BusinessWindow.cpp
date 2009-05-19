#include "BusinessWindow.h"
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
#include "BusinessDetailWidget.h"
#include "BusinessTypeEditor.h"
#include "UiStrings.h"
#include "MessageBox.h"

BusinessWindow::BusinessWindow(QWidget *parent)
:QMainWindow(parent),m_started(false),m_typeEditor(NULL)
{

	m_businessTypeNames = AnythingFactory<ArrayUint32String>::instance()->createAnything(BUSINESSTYPE);	

	ui.setupUi(this);
	ui.itemView->installEventFilter(this);
	ui.menubar->installEventFilter(this);
	ui.toolBar->installEventFilter(this);

	m_searchBox = new SearchBox(this);
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmIdStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmTypeStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmNameStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmBrandStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmRatingStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmSpecificationStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmPriceStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmDiscountStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmDescriptionStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmBuysStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmSalesStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(bmStocksStr));
	
	m_detailWidget = new BusinessDetailWidget(this);
	ui.sideBar->addWidget(m_detailWidget, 0, 0);
	ui.sideBar->addWidget(m_searchBox, 1, 0);
	
	connect(m_searchBox, SIGNAL(regExpChanged(QRegExp &)), 
		ui.itemView, SLOT(changeRegExp(QRegExp &)));
	connect(m_searchBox, SIGNAL(columnChanged(int)), 
		ui.itemView, SLOT(changeFilterColumn(int)));
	connect(m_searchBox, SIGNAL(sortChanged(int)), 
		ui.itemView, SLOT(changeSortCase(int)));
	connect(m_detailWidget, SIGNAL(submittedBusiness(Business*, QByteArray&, uint32)), 
		this, SLOT(submitBusiness(Business*, QByteArray&, uint32)));
		connect(ui.itemView, SIGNAL(itemActivated(int, int, QVariant &)), 
			this, SLOT(viewItemActivated(int, int, QVariant &)));
}

BusinessWindow::~BusinessWindow()
{
	delete m_typeEditor;
	delete m_searchBox;
	delete m_detailWidget;
}

void BusinessWindow::changeEvent(QEvent *e)
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

bool BusinessWindow::event(QEvent* ev){
	switch(ev->type()) {
		case QEvent::Show:
		{
			if(!m_started) {
				m_started = true;
				getBusinessType();
				getAllBusiness();
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


bool BusinessWindow::eventFilter(QObject* obj, QEvent* ev){
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


void BusinessWindow::OnEvent(Message& Msg){
	switch(Msg.type())
	{
		case EVENT_BUSINESSMGNT:
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
		case EVENT_BUSINESSTYPE:
			{
				m_businessTypeCache.clear();
				m_businessTypeNames->clear();
				list<BusinessType>* data = static_cast<list<BusinessType>*>(Msg.data());
				for(list<BusinessType>::iterator it = data->begin() ; it != data->end() ; it++) {
					m_businessTypeCache[it->getId()] = *it;
					m_businessTypeNames->insert(pair<uint32, string>(it->getId(), it->getName()));
				}

				m_detailWidget->setBusinessTypes(data);
				if(NULL != m_typeEditor)
					m_typeEditor->addBusinessType(data);
				break;
			}
		case	EVENT_ALLBUSINESS:
			{
				addBusiness2View(static_cast<list<Business>*>(Msg.data()));
				break;
			}
		case	EVENT_BUSINESS:
			{
				if(NULL != Msg.data())
					m_detailWidget->browseBusiness(static_cast<Business*>(Msg.data()));
				break;
			}
		case	EVENT_BUSINESSPIC:
			{
				if(NULL != Msg.data()) {
					QByteArray* image = static_cast<QByteArray*>(Msg.data());
					m_detailWidget->displayPicture(*image);
					delete image;
				} else {
					m_detailWidget->clearPicture();
				}
				break;
			}
		case	EVENT_ADDBUSINESS:
			{
				if(NULL != Msg.data()) {
					Business* data = static_cast<Business*>(Msg.data());
					addBusiness2View(data);
					m_detailWidget->browseBusiness(data);
					if(NULL != Msg.data2()) {
						QByteArray* image = static_cast<QByteArray*>(Msg.data2());
						m_detailWidget->displayPicture(*image);
						delete image;
					}
				} else {
					MessageBox::showMessageBox(this, QMessageBox::Critical, 
						bmString, bmAddBusinessErrorStr);
				}
				break;
			}
		case	EVENT_REMOVEBUSINESS:
			{
				if(NULL != Msg.data()) {
					getAllBusiness();
					m_detailWidget->clearPicture();
					Business* emptyBusiness = new Business;
					emptyBusiness->clear();
					m_detailWidget->browseBusiness(emptyBusiness);
					delete emptyBusiness;
				} else {
					MessageBox::showMessageBox(this, QMessageBox::Critical, bmString, removeError);
				}
				break;
			}
		case	EVENT_MODIFYBUSINESS:
			{
				if(NULL != Msg.data()) {
					Business* data = static_cast<Business*>(Msg.data());
					m_detailWidget->browseBusiness(data);
					if(NULL != Msg.data2()) {
						QByteArray* image = static_cast<QByteArray*>(Msg.data2());
						m_detailWidget->displayPicture(*image);
						delete image;
					}
					getAllBusiness();
				} else {
					MessageBox::showMessageBox(this, QMessageBox::Critical, 
						bmString, bmModifyBusinessErrorStr);
				}
				break;
			}
		case	EVENT_BUSINESSRECORD:
			{
				break;
			}
		case	EVENT_SETBUSINESSTYPE:
			{
				list<BusinessType>* error = static_cast<list<BusinessType>*>(Msg.data());
				getBusinessType();
				if(NULL!= error && !error->empty()){
					string errorstr = bmTypeStr;
					for(list<BusinessType>::iterator it = error->begin() ; it != error->end() ; it++) {
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
		default: break;
	}
}


void BusinessWindow::addBusiness(Business* business, QByteArray& image){
	Message* action = new Message(ACTION_ADDBUSINESS, business, &image);
	m_uiHandler->StartAction(*action);
	delete action;
}

void BusinessWindow::viewItemActivated(int row, int column, QVariant & data){
	getBusiness(ui.itemView->sibling(row, 0).toUInt());
}

void BusinessWindow::addBusiness2View(list<Business>* data)
{
	list<Business>::iterator it = data->begin();
	while(data->end() != it) {
		addBusiness2View(&(*it));
		it++;
	}
}

void BusinessWindow::addBusiness2View(Business* data)
{
	ui.itemView->addBusiness(*data);	
}

void BusinessWindow::dealAction(QAction* action){
	if(action == ui.actionMenu) { Menu(); return; }
	if(action == ui.actionLogOff) { Logoff(); return; }
	if(action == ui.actionExit) { Exit(); return; }
	if(action == ui.actionRemove) { removeBusiness(); return; }
	if(action == ui.actionAdd) { addBusiness(); return; }
	if(action == ui.actionEdit) { editBusiness(); return; }
	if(action == ui.actionQuery) { TOBE_REALIZIED; return; }
	if(action == ui.actionTypeSetting) { typeSetting(); return; }
	if(action == ui.actionAboutCosmetic) { TOBE_REALIZIED; return; }
	if(action == ui.actionLock) { TOBE_REALIZIED; return; }
	if(action == ui.actionSmallIcon) { showSmallIcon(ui.actionSmallIcon->isChecked()); return; }
	if(action == ui.actionTextLabel) { showTextLabel(ui.actionTextLabel->isChecked()); return; }
	if(action == ui.actionToolBar) { showToolBar(ui.actionToolBar->isChecked()); return; }
}

void BusinessWindow::removeBusiness()	
{
	int row = 0;
	int col = 0;
	ui.itemView->currentIndex(row, col);
	uint32 currentID = ui.itemView->sibling(row, 0).toUInt();
	if(0 != currentID) {
		string  currentName = string(ui.itemView->sibling(row, 1).toString().toLocal8Bit().data());
		QString confirm =LOCAL8BITSTR(bmRemoveBusinessConfirm).
			arg(LOCAL8BITSTR(currentName.c_str()));
		if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, 
			bmString, confirm.toLocal8Bit().data())) return;
	} else {
		MessageBox::showMessageBox(this, QMessageBox::Warning, bmString, zeroSelectionWarning);
	}
}

void BusinessWindow::editBusiness()
{
	ui.sideBar->showSideBar(true);
	m_detailWidget->editBusiness(NULL);
}

void BusinessWindow::addBusiness()
{
	ui.sideBar->showSideBar(true);
	m_detailWidget->newBusiness();
}

void BusinessWindow::getAllBusiness(){
	Message* action = new Message(ACTION_GETALLBUSINESS);
	m_uiHandler->StartAction(*action);
	delete action;
}


void BusinessWindow::getBusiness(uint32 id){
	uint32* id1 = new uint32(id);
	uint32* id2 = new uint32(id);
	Message* action1 = new Message(ACTION_GETBUSINESS, id1);
	m_uiHandler->StartAction(*action1);
	delete action1;
	Message* action2 = new Message(ACTION_GETBUSINESSPIC, id2);
	m_uiHandler->StartAction(*action2);
	delete action2;
}


void BusinessWindow::getBusinessType(){
	Message* action = new Message(ACTION_GETBUSINESSTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}


void BusinessWindow::modifyBusiness(Business* business, QByteArray& image){
	Message* action = new Message(ACTOIN_MODIFYBUSINESS, business, &image);
	m_uiHandler->StartAction(*action);
	delete action;
}


void BusinessWindow::removeBusiness(uint32 id){
	uint32* id1 = new uint32(id);
	Message* action = new Message(ACTION_REMOVEBUSINESS, id1);
	m_uiHandler->StartAction(*action);
	delete action;

}


void BusinessWindow::setBusinessType(list<BusinessType>* data){
	Message* action = new Message(ACTION_SETBUSINESSTYPE, data);
	m_uiHandler->StartAction(*action);
	delete action;

}

void BusinessWindow::Menu()
{
	Message* action = new Message(ACTION_MAINMENU);
	m_uiHandler->StartAction(*action);
	delete action;
}

void BusinessWindow::Logoff()
{
	Message* action = new Message(ACTION_LOGOFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void BusinessWindow::Exit()
{
	Message* action = new Message(ACTION_EXIT);
	m_uiHandler->StartAction(*action);
	delete action;
}

void BusinessWindow::showSmallIcon(bool flag)
{
	if(flag) {
		ui.toolBar->setIconSize(QSize(32, 32));
	} else {
		ui.toolBar->setIconSize(QSize(48, 48));
	}
}

void BusinessWindow::showTextLabel(bool flag)
{
	if(flag) {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	} else {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	}
}

void BusinessWindow::showToolBar(bool flag)
{
	if(flag) {
		ui.toolBar->show();
	} else {
		ui.toolBar->close();
	}
}

void BusinessWindow::typeSetting()
{
	m_typeEditor = new BusinessTypeEditor(this);
	m_typeEditor->setWindowModality(Qt::WindowModal);
	m_typeEditor->setWindowFlags(Qt::Popup);
	connect(m_typeEditor, SIGNAL(submitted(void*)), 
		this, SLOT(setBusinessType(list < BusinessType >*)));
	m_typeEditor->changeMode(ItemEditor::EditMode);
	for(BusinessTypeArray::const_iterator it = m_businessTypeCache.begin() ; m_businessTypeCache.end() != it ; it++)
		m_typeEditor->addBusinessType(it->second);
	m_typeEditor->show();
}

void BusinessWindow::submitBusiness(Business* data, QByteArray& picData, uint32 mode)
{
	if(BusinessDetailWidget::BUSINESS_NEW == mode)
		addBusiness(data, picData);
	if(BusinessDetailWidget::BUSINESS_MODIFY == mode)
		modifyBusiness(data, picData);
}