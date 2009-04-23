#include "SSMainMenu.h"
#include "Singleton.cpp"
#include "SSMainHandler.h"
#include "Message.h"
#include "Staff.h"
#include "messagedef.h"
#define SM_X (0)
#define SM_Y (0)
#define SO_X (0)
#define SO_Y (1)
#define LO_X (1)
#define LO_Y (2)
SSMainMenu::SSMainMenu(QWidget *parent, DUIHandler* handler)
: QDialog(parent)
{
	ui.setupUi(this);
	createIcons();
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
//			ui.infoLabel->setText(QString::fromLocal8Bit("您好，") + QString::fromLocal8Bit(Logged->Name().c_str()) + 
//				QString::fromLocal8Bit("！\n欢迎使用Cosmetic（科思美）美容美发业运营系统。"));
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

void SSMainMenu::startFunction(int x, int y)
{
	Message* action = new Message();
	
	if(LO_X == x && LO_Y == y)
		action->setType(ACTION_LOGOFF);
	else if(SM_X == x && SM_Y == y)
		action->setType(ACTION_STAFFMGNT);

	m_uiHandler->StartAction(*action);
	delete action;
}

void SSMainMenu::createIcons()
 {
	 ui.FunctionTableWidget->setColumnWidth(0, 128);
	 ui.FunctionTableWidget->setColumnWidth(1, 128);
	 ui.FunctionTableWidget->setColumnWidth(2, 128);
	 ui.FunctionTableWidget->setRowHeight(0, 128);
	 ui.FunctionTableWidget->setRowHeight(1, 128);
     QTableWidgetItem *staffButton = new QTableWidgetItem(QString::fromLocal8Bit("员工管理"));
     staffButton->setIcon(QIcon(":/staff/Resources/people.png"));
     staffButton->setTextAlignment(Qt::AlignCenter);
     staffButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	 ui.FunctionTableWidget->setItem(SM_X, SM_Y, staffButton);
	 
     QTableWidgetItem *operationButton = new QTableWidgetItem(QTableWidgetItem::Type);
     operationButton->setIcon(QIcon(":/staff/Resources/level.png"));
     operationButton->setText(QString::fromLocal8Bit("店面运营"));
     operationButton->setTextAlignment(Qt::AlignCenter);
     operationButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	 ui.FunctionTableWidget->setItem(SO_X, SO_Y, operationButton);

     QTableWidgetItem *logoffButton = new QTableWidgetItem(QTableWidgetItem::Type);
     logoffButton->setIcon(QIcon(":/staff/Resources/staff.png"));
     logoffButton->setText(QString::fromLocal8Bit("注销"));
     logoffButton->setTextAlignment(Qt::AlignCenter);
     logoffButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	 ui.FunctionTableWidget->setItem(LO_X, LO_Y, logoffButton);

	connect(ui.FunctionTableWidget, SIGNAL(cellActivated(int, int)), this, SLOT(startFunction(int, int)));
 }
