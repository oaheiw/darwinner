#include "entry.h"
#include "MainDispatcher.h"
#include <string>
#include "Singleton.cpp"
#include "messagedef.h"
#include "Staff.h"
#include "Message.h"

entry::entry(QWidget *parent, Qt::WFlags flags , DUIHandler* handler)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	m_uiHandler = handler;
}

entry::~entry()
{

}

void entry::OnEvent(Message& ev) 
{
	switch(ev.type()) {
		case EVENT_LOGGEDIN:
		{
			hide();
			break;
		}
		case EVENT_SYSTEM_START:
		case EVENT_LOGGEDOFF:
		{
			show();
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

void entry::on_pushButtonLogin_clicked()
{
	Staff* stu = new Staff();
	stu->SetID(ui.lineEditID->text().toStdString());
	stu->SetPassword(ui.lineEditPW->text().toStdString());
	Message* action = new Message(stu);
	action->setType(ACTION_LOGIN);
	m_uiHandler->StartAction(*action);
	delete action;
}