#include "SSLoginWindow.h"
#include <string>
#include "messagedef.h"
#include "Staff.h"
#include "Message.h"
#include "DUIHandler.h"

SSLoginWindow::SSLoginWindow(QWidget *parent, Qt::WFlags flags , DUIHandler* handler)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	m_uiHandler = handler;
	const QIcon icon = QIcon(QString::fromUtf8(":/icons/Resources/Cosmetic.png"));
    setWindowIcon(icon);
}

SSLoginWindow::~SSLoginWindow()
{

}

void SSLoginWindow::OnEvent(Message& ev) 
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

void SSLoginWindow::on_pushButtonLogin_clicked()
{
	Staff* stu = new Staff();
	stu->SetID(ui.lineEditID->text().toUInt());
	stu->SetPassword(ui.lineEditPW->text().toStdString());
	Message* action = new Message(stu);
	action->setType(ACTION_LOGIN);
	m_uiHandler->StartAction(*action);
	delete action;
}