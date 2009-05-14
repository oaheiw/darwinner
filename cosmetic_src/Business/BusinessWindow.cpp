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
:QMainWindow(parent),m_started(false)
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
	
	connect(m_searchBox, SIGNAL(regExpChanged(QRegExp &)), ui.itemView, SLOT(changeRegExp(QRegExp &)));
	connect(m_searchBox, SIGNAL(columnChanged(int)), ui.itemView, SLOT(changeFilterColumn(int)));
	connect(m_searchBox, SIGNAL(sortChanged(int)), ui.itemView, SLOT(changeSortCase(int)));

//	connect(staffDetailWidget, SIGNAL(addedStaff(Staff*, QByteArray&)), this, SLOT(addStaff(Staff*, QByteArray&)));
//	connect(staffDetailWidget, SIGNAL(modifiedStaff(Staff*, QByteArray&)), this, SLOT(modifyStaff(Staff*, QByteArray&)));

	
}

BusinessWindow::~BusinessWindow()
{

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
			DBHEX("start bm window.", "");
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
	}
}


void BusinessWindow::addBusiness(Business* business, QByteArray& image){
	Message* action = new Message(ACTION_ADDBUSINESS, business, &image);
	m_uiHandler->StartAction(*action);
	delete action;
}

void BusinessWindow::viewItemActivated(int row, int column, QVariant & data){

}

void BusinessWindow::addBusiness2View(list<Business>* data)
{
	list<Business>::iterator it = data->begin();
	int row = 0;
	while(data->end() != it) {
		ui.itemView->addBusiness(*it);
		it++;
	}
}


void BusinessWindow::businessTypeSetting(){

}


void BusinessWindow::dealAction(QAction* action){
	if(action == ui.actionMenu) { Menu(); return; }
	if(action == ui.actionLogOff) { Logoff(); return; }
	if(action == ui.actionExit) { Exit(); return; }
	if(action == ui.actionRemove) { TOBE_REALIZIED; return; }
	if(action == ui.actionAdd) { TOBE_REALIZIED; return; }
	if(action == ui.actionEdit) { TOBE_REALIZIED; return; }
	if(action == ui.actionQuery) { TOBE_REALIZIED; return; }
	if(action == ui.actionTypeSetting) { typeSetting(); return; }
	if(action == ui.actionAboutCosmetic) { TOBE_REALIZIED; return; }
	if(action == ui.actionLock) { TOBE_REALIZIED; return; }
	if(action == ui.actionSmallIcon) { showSmallIcon(ui.actionSmallIcon->isChecked()); return; }
	if(action == ui.actionTextLabel) { showTextLabel(ui.actionTextLabel->isChecked()); return; }
	if(action == ui.actionToolBar) { showToolBar(ui.actionToolBar->isChecked()); return; }
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
	BusinessTypeEditor* editor = new BusinessTypeEditor(this);
	editor->setWindowModality(Qt::WindowModal);
	editor->setWindowFlags(Qt::Tool);
	connect(editor, SIGNAL(submitted(void* data)), this, SLOT(setBusinessType(list < BusinessType > *)));
	editor->changeMode(ItemEditor::EditMode);
	for(BusinessTypeArray::const_iterator it = m_businessTypeCache.begin() ; m_businessTypeCache.end() != it ; it++)
		editor->addBusinessType(it->second);
	editor->show();
}

