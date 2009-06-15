#include "StockWindow.h"
#include "messagedef.h"
#include "Message.h"
#include <QContextMenuEvent>

StockWindow::StockWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
