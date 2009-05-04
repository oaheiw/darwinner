#include "BusinessWindow.h"
#include <QByteArray>
#include <QEvent>
#include <QPoint>
#include <QContextMenuEvent>
#include "DUIHandler.h"
#include "Message.h"
#include "messagedef.h"
#include "SearchBox.h"
#include "BusinessDetailWidget.h"
#include "UiStrings.h"
#include "MessageBox.h"

BusinessWindow::BusinessWindow(QWidget *parent)
:QMainWindow(parent)
{
 	ui.setupUi(this);
	m_started = false;

	ui.itemView->installEventFilter(this);
	ui.menubar->installEventFilter(this);
	ui.toolBar->installEventFilter(this);

	m_searchBox = new SearchBox(this);
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmIdStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmTypeStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmNameStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmBrandStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmRatingStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmSpecificationStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmPriceStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmDiscountStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmDescriptionStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmBuysStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmSalesStr));
	m_searchBox->addFilterItem(LOCAL8BITSTR(UiStr::bmStocksStr));
	
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
			DBINFO("start bm window.", "");
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
		int col = 0;
		ui.itemView->addData(row, col++, it->id());
		ui.itemView->addData(row, col++, LOCAL8BITSTR(m_businessTypeCache[it->type()].getName().c_str()));
		ui.itemView->addData(row, col++, LOCAL8BITSTR(it->name().c_str()));
		ui.itemView->addData(row, col++, LOCAL8BITSTR(it->brand().c_str()));
		ui.itemView->addData(row, col++, it->getRating());
		ui.itemView->addData(row, col++, LOCAL8BITSTR(it->specification().c_str()));
		ui.itemView->addData(row, col++, it->price());
		ui.itemView->addData(row, col++, it->discount());
		ui.itemView->addData(row, col++, LOCAL8BITSTR(it->description().c_str()));
		ui.itemView->addData(row, col++, it->buys());
		ui.itemView->addData(row, col++, it->sales());
		ui.itemView->addData(row, col++, it->stocks());
		row++;
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
	if(action == ui.actionTypeSetting) { TOBE_REALIZIED; return; }
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

