#include "BusinessManagementUI.h"
#include "messagedef.h"
#include "Message.h"
#include "DUIHandler.h"
#include <QEvent>
#include "BusinessItemView.h"
#include "DateBox.h"
#include "SearchBox.h"


BusinessManagementUI::BusinessManagementUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	dateBox = new DateBox(this);
	searchBox = new SearchBox(this); 
	
	ui.sideBarWidget->addWidget(dateBox, 0, 0);
	ui.sideBarWidget->addWidget(searchBox, 1, 0);

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
//			dateBox->moveCalendar();
			break;
		}
	}
	return QMainWindow::event(ev);
}

bool BusinessManagementUI::eventFilter(QObject * obj,QEvent * ev)
{
	return QMainWindow::eventFilter(obj, ev);
}