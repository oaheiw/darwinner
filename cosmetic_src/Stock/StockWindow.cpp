#include "StockWindow.h"
#include "messagedef.h"
#include "Message.h"
#include <QContextMenuEvent>
#include "UiStrings.h"
#include "MessageBox.h"
#include "DUIHandler.h"
#include "Business.h"
#include "Stock.h"
#include "Inventory.h"

StockWindow::StockWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.commodityList->installEventFilter(this);
	ui.StockingList->installEventFilter(this);
	ui.inventoryList->installEventFilter(this);
	ui.menubar->installEventFilter(this);
	ui.toolBar->installEventFilter(this);

	connect(ui.commodityList, SIGNAL(itemActivated(int, int, QVariant &)), 
		this, SLOT(viewItemActivated(int, int, QVariant &)));
}

StockWindow::~StockWindow()
{

}

void StockWindow::changeEvent(QEvent *e)
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

bool StockWindow::event(QEvent* ev){
	switch(ev->type()) {
		case QEvent::Show:
			{
				if(!m_started) {
					m_started = true;
					getAllCommodities();
				}
				showMaximized();
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


bool StockWindow::eventFilter(QObject* obj, QEvent* ev){
	switch(ev->type()) {
		case QEvent::ContextMenu:
			{
				QMenu menu(this);
				if(ui.commodityList == obj) {
					menu.addAction(ui.actionAdd);
					menu.addAction(ui.actionRemove);
					menu.addAction(ui.actionInventory);
				} else if(ui.toolBar == obj || ui.menubar == obj) {
					menu.addAction(ui.actionSmallIcon);
					menu.addAction(ui.actionTextLabel);
					menu.addAction(ui.actionToolBar);
				} else {
					ev->accept();
					return true;
				}
				menu.exec(dynamic_cast<QContextMenuEvent*>(ev)->globalPos());
				ev->accept();
				return true;
			}
	}
	return QMainWindow::eventFilter(obj, ev);
}


void StockWindow::OnEvent(Message& Msg){
	switch(Msg.type())
	{
	case EVENT_STOCKMGNT:
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
	default: break;
	}
}

void StockWindow::dealAction(QAction* action){
	if(action == ui.actionMenu) { Menu(); return; }
	if(action == ui.actionLogOff) { Logoff(); return; }
	if(action == ui.actionExit) { Exit(); return; }
	if(action == ui.actionRemove) { newStock(STOCKING_OUT); return; }
	if(action == ui.actionAdd) { newStock(STOCKING_IN); return; }
	if(action == ui.actionInventory) { newInventory(); return; }
	if(action == ui.actionBatchCheck) { newBatchInventory(); return; }
	if(action == ui.actionWarning) { stockSetting(); return; }
	if(action == ui.actionAboutCosmetic) { TOBE_REALIZIED; return; }
	if(action == ui.actionLock) { TOBE_REALIZIED; return; }
	if(action == ui.actionSmallIcon) { showSmallIcon(ui.actionSmallIcon->isChecked()); return; }
	if(action == ui.actionTextLabel) { showTextLabel(ui.actionTextLabel->isChecked()); return; }
	if(action == ui.actionToolBar) { showToolBar(ui.actionToolBar->isChecked()); return; }
}

void StockWindow::viewItemActivated(int row, int column, QVariant & data){
	uint32 id = ui.commodityList->sibling(row, 0).toUInt();
	getStock(id);
	getInventory(id);
}

void StockWindow::getAllCommodities()
{
	Message* action = new Message(ACTION_GETCOMMODITIES);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::addCommodity2View(list<Business>* data)
{
	ui.commodityList->clearData();
	list<Business>::iterator it = data->begin();
	while(data->end() != it) {
		ui.commodityList->addBusiness(*it);
		it++;
	}
}

void StockWindow::getStock(uint32 id)
{
	uint32* pid = new uint32(id);
	Message* action = new Message(ACTION_GETSTOCKING, pid);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::addStock2View(list<Stock>* data)
{
	ui.StockingList->clearData();
	list<Stock>::iterator it = data->begin();
	while(data->end() != it) {
		ui.StockingList->addStocking(*it);
		it++;
	}
}

void StockWindow::getInventory(uint32 id)
{
	uint32* pid = new uint32(id);
	Message* action = new Message(ACTION_GETINVENTORY, pid);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::addInventory2View(list<Inventory>* data)
{
	ui.inventoryList->clearData();
	list<Inventory>::iterator it = data->begin();
	while(data->end() != it) {
		ui.inventoryList->addInventory(*it);
		it++;
	}
}

void StockWindow::stockSetting()
{
	TOBE_REALIZIED;
}

void StockWindow::newStock(STOCKING_DIRECTION direction)
{
	TOBE_REALIZIED;
}

void StockWindow::newInventory()
{
	int row = 0;
	int col = 0;
	ui.commodityList->currentIndex(row, col);
	uint32* id = new uint32(ui.commodityList->sibling(row, 0).toUInt());
	Message* action = new Message(ACTION_CHECKINVENTORY, id);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::newBatchInventory(){
	//batch action here
	uint32* id = new uint32(0);
	Message* action = new Message(ACTION_CHECKINVENTORY, id);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::submitStock(Stock* data){
	Message* action = new Message(data);

	if(STOCKING_IN == data->getDirction()) {
		action->setType(ACTION_STOCKIN);
	} else if(STOCKING_OUT == data->getDirction()) {
		action->setType(ACTION_STOCKOUT);
	} else {
		MessageBox::showMessageBox
			(this, QMessageBox::Critical, stString, stDirectionErrorStr);
		return;
	}
	
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::submitInventory(Inventory* data)
{
	Message* action = new Message(ACTION_SUBMITINVENTORY, data);
	GetHandler()->StartAction(*action);
	delete action;
}
void StockWindow::submitWarningLevel(uint32 value)
{
	uint32* data = new uint32(value);
	Message* action = new Message(ACTION_SETSTOCKWARNINGLEVEL, data);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::submitCheckDate(short date)
{
	uint32* data = new uint32(date);
	Message* action = new Message(ACTION_SETCHECKDATE, data);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::Menu()
{
	Message* action = new Message(ACTION_MAINMENU);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::Logoff()
{
	Message* action = new Message(ACTION_LOGOFF);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::Exit()
{
	Message* action = new Message(ACTION_EXIT);
	GetHandler()->StartAction(*action);
	delete action;
}

void StockWindow::showSmallIcon(bool flag)
{
	if(flag) {
		ui.toolBar->setIconSize(QSize(32, 32));
	} else {
		ui.toolBar->setIconSize(QSize(48, 48));
	}
}

void StockWindow::showTextLabel(bool flag)
{
	if(flag) {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	} else {
		ui.toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	}
}

void StockWindow::showToolBar(bool flag)
{
	if(flag) {
		ui.toolBar->show();
	} else {
		ui.toolBar->close();
	}
}