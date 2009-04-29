#include "BusinessManagementUI.h"
#include "messagedef.h"
#include "Message.h"
#include "DUIHandler.h"
#include <QEvent>


BusinessManagementUI::BusinessManagementUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

BusinessManagementUI::~BusinessManagementUI()
{

}

void BusinessManagementUI::OnEvent(Message & Msg)
{
	switch(Msg.type())
	{
		case EVENT_BUSINESSMGNT:
		{
			if(isHidden())
				show();
			else
				setFocus();
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

bool BusinessManagementUI::event(QEvent * ev)
{
	switch(ev->type()) {
		case QEvent::Resize:
		case QEvent::Move:
		{
			ui.dateBoxWidget->moveCalendar();
			break;
		}
	}
	return QMainWindow::event(ev);
}

bool BusinessManagementUI::eventFilter(QObject * obj,QEvent * ev)
{
	return QMainWindow::eventFilter(obj, ev);
}