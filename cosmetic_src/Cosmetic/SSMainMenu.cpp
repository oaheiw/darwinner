#include "SSMainMenu.h"
#include "Singleton.h"
#include "SSMainHandler.h"
#include "Message.h"
#include "Staff.h"
#include "messagedef.h"

const short SM_X = 0;
const short  SM_Y = 0;
const short  SO_X = 0;
const short  SO_Y = 1;
const short  BM_X = 1;
const short  BM_Y = 0;
const short  LO_X = 2;
const short  LO_Y = 1;
const short EX_X = 2;
const short EX_Y = 2;

const QRgb COLOR_1 = 0x00FBCE6C;
const QRgb COLOR_2 = 0x00FB6C6C;
const QRgb COLOR_3 = 0x00BFC6FF;
const QRgb COLOR_4 = 0x008B93DF;
const QRgb COLOR_5 = 0x0095D591;
const QRgb COLOR_6 = 0x00FAC1FF;
const QRgb COLOR_7 = 0x00FBB1F5;
const QRgb COLOR_8 = 0x00F385BC;
const QRgb COLOR_9 = 0x00FFE36A;

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
			int* r = static_cast<int*>(ev.data());
			if(ERROR_NO_ERROR == *r) {
				show();
			}
			delete r;
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
	else if(BM_X == x && BM_Y == y)
		action->setType(ACTION_BUSINESSMGNT);
	else if(EX_X == x && EX_Y == y)
		action->setType(ACTION_EXIT);

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
	ui.FunctionTableWidget->setRowHeight(2, 128);


	QTableWidgetItem *staffButton = new QTableWidgetItem(LOCAL8BITSTR(smString));
	staffButton->setIcon(QIcon(":/staff/Resources/people.png"));
	staffButton->setTextAlignment(Qt::AlignCenter);
	staffButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	staffButton->setBackgroundColor(QColor(COLOR_1));
	ui.FunctionTableWidget->setItem(SM_X, SM_Y, staffButton);

	QTableWidgetItem *operationButton = new QTableWidgetItem(QTableWidgetItem::Type);
	operationButton->setIcon(QIcon(":/common/shop"));
	operationButton->setText(LOCAL8BITSTR(soString));
	operationButton->setTextAlignment(Qt::AlignCenter);
	operationButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	operationButton->setBackgroundColor(QColor(COLOR_2));
	ui.FunctionTableWidget->setItem(SO_X, SO_Y, operationButton);

	QTableWidgetItem *businessButton = new QTableWidgetItem(QTableWidgetItem::Type);
	businessButton->setIcon(QIcon(":/common/business"));
	businessButton->setText(LOCAL8BITSTR(bmString));
	businessButton->setTextAlignment(Qt::AlignCenter);
	businessButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	businessButton->setBackgroundColor(QColor(COLOR_4));
	ui.FunctionTableWidget->setItem(BM_X, BM_Y, businessButton);

	QTableWidgetItem *logoffButton = new QTableWidgetItem(QTableWidgetItem::Type);
	logoffButton->setIcon(QIcon(":common/logoff"));
	logoffButton->setText(LOCAL8BITSTR(logoffString));
	logoffButton->setTextAlignment(Qt::AlignCenter);
	logoffButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	logoffButton->setBackgroundColor(QColor(COLOR_8));
	ui.FunctionTableWidget->setItem(LO_X, LO_Y, logoffButton);

	QTableWidgetItem *exitButton = new QTableWidgetItem(QTableWidgetItem::Type);
	exitButton->setIcon(QIcon(":/common/logout"));
	exitButton->setText(LOCAL8BITSTR(exitString));
	exitButton->setTextAlignment(Qt::AlignCenter);
	exitButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	exitButton->setBackgroundColor(QColor(COLOR_9));
	ui.FunctionTableWidget->setItem(EX_X, EX_Y, exitButton);

	connect(ui.FunctionTableWidget, SIGNAL(cellActivated(int, int)), this, SLOT(startFunction(int, int)));
 }

