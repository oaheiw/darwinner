#include "DarwinMain.h"
#include "Singleton.cpp"
#include "MainDispatcher.h"
#include "Message.h"
#include "Stuff.h"
DarwinMain::DarwinMain(QWidget *parent, DUIHandler* handler)
: QDialog(parent)
{
	ui.setupUi(this);
	m_uiHandler = handler;
}

DarwinMain::~DarwinMain()
{

}

void DarwinMain::OnEvent(Message& ev) 
{
	switch(ev.type()) {
		case EVENT_LOGGEDIN:
		{
			Stuff* Logged = (Stuff*)(ev.data());
			ui.labelInfo->setText(QString::fromLocal8Bit("ÄúºÃ£¬") + QString::fromLocal8Bit(Logged->Name().c_str()));
			show();
			break;
		}
		case EVENT_LOGGEDOFF:
		{
			hide();
			break;
		}
		case EVENT_EXIT:
		{
			close();
			break;
		}
		default:
		{
			hide();
			break;
		}
	}

}

void DarwinMain::on_pushButtonLogoff_clicked()
{
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void DarwinMain::on_pushButtonStuffMgnt_clicked()
{
	Message* action = new Message();
	action->setType(ACTION_STUFFMGNT);
	m_uiHandler->StartAction(*action);
	delete action;
}
