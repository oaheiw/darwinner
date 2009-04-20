#include "SSMainMenu.h"
#include "Singleton.cpp"
#include "SSMainHandler.h"
#include "Message.h"
#include "Staff.h"
#include "messagedef.h"

SSMainMenu::SSMainMenu(QWidget *parent, DUIHandler* handler)
: QDialog(parent)
{
	ui.setupUi(this);
	m_uiHandler = handler;
	const QIcon icon = QIcon(QString::fromUtf8(":/common/Resources/Cosmetic.png"));
    setWindowIcon(icon);
}

SSMainMenu::~SSMainMenu()
{

}

void SSMainMenu::OnEvent(Message& ev) 
{
	switch(ev.type()) {
		case EVENT_LOGGEDIN:
		{
			Staff* Logged = (Staff*)(ev.data());
			ui.labelInfo->setText(QString::fromLocal8Bit("ÄúºÃ£¬") + QString::fromLocal8Bit(Logged->Name().c_str()));
			show();
			break;
		}
		case EVENT_MAINMENU:
		{
			show();
			break;
		}
		case EVENT_EXIT:
		{
			close();
			break;
		}
		case EVENT_LOGGEDOFF:
		default:
		{
			hide();
			break;
		}
	}

}

void SSMainMenu::on_pushButtonLogoff_clicked()
{
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void SSMainMenu::on_pushButtonStaffMgnt_clicked()
{
	Message* action = new Message();
	action->setType(ACTION_STAFFMGNT);
	m_uiHandler->StartAction(*action);
	delete action;
}