#include "SSMainMenu.h"
#include "Singleton.h"
#include "SSMainHandler.h"
#include "Message.h"
#include "Staff.h"
#include "messagedef.h"
#include "UiStrings.h"
#include <QPainter>
#include <QBitmap>

const short SM_X = 0;
const short SM_Y = 0;
const short SO_X = 0;
const short SO_Y = 1;
const short BM_X = 0;
const short BM_Y = 2;

const short CM_X = 1;
const short CM_Y = 0;
const short ST_X = 1;
const short ST_Y = 1;
const short RS_X = 1;
const short RS_Y = 2;

const short CF_X = 2;
const short CF_Y = 0;
const short LO_X = 2;
const short LO_Y = 1;
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

SSMainMenu::SSMainMenu(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	createIcons();
	const QIcon icon = 
		QIcon(QString::fromUtf8(":/common/Resources/Cosmetic.png"));
    setWindowIcon(icon);
	roundCorner();
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
	else if(CM_X == x && CM_Y == y)
		action->setType(ACTION_CUSTOMERMGNT);
	else if(ST_X == x && ST_Y == y)
		action->setType(ACTION_STOCKMGNT);

	GetHandler()->StartAction(*action);
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

	ui.FunctionTableWidget->item(SM_X, SM_Y)->setText(LOCAL8BITSTR(smString));
	ui.FunctionTableWidget->item(SM_X, SM_Y)->setBackgroundColor(QColor(COLOR_1));

	ui.FunctionTableWidget->item(SO_X, SO_Y)->setText(LOCAL8BITSTR(soString));
	ui.FunctionTableWidget->item(SO_X, SO_Y)->setBackgroundColor(QColor(COLOR_2));

	ui.FunctionTableWidget->item(BM_X, BM_Y)->setText(LOCAL8BITSTR(bmString));
	ui.FunctionTableWidget->item(BM_X, BM_Y)->setBackgroundColor(QColor(COLOR_3));	

	ui.FunctionTableWidget->item(CM_X, CM_Y)->setText(LOCAL8BITSTR(cmString));
	ui.FunctionTableWidget->item(CM_X, CM_Y)->setBackgroundColor(QColor(COLOR_4));	

	ui.FunctionTableWidget->item(ST_X, ST_Y)->setText(LOCAL8BITSTR(stString));
	ui.FunctionTableWidget->item(ST_X, ST_Y)->setBackgroundColor(QColor(COLOR_5));	

	ui.FunctionTableWidget->item(RS_X, RS_Y)->setText(LOCAL8BITSTR(rsString));
	ui.FunctionTableWidget->item(RS_X, RS_Y)->setBackgroundColor(QColor(COLOR_6));	

	ui.FunctionTableWidget->item(CF_X, CF_Y)->setText(LOCAL8BITSTR(cfString));
	ui.FunctionTableWidget->item(CF_X, CF_Y)->setBackgroundColor(QColor(COLOR_7));	

	ui.FunctionTableWidget->item(LO_X, LO_Y)->setText(LOCAL8BITSTR(logoffString));
	ui.FunctionTableWidget->item(LO_X, LO_Y)->setBackgroundColor(QColor(COLOR_8));	

	ui.FunctionTableWidget->item(EX_X, EX_Y)->setText(LOCAL8BITSTR(exitString));
	ui.FunctionTableWidget->item(EX_X, EX_Y)->setBackgroundColor(QColor(COLOR_9));	

	connect(ui.FunctionTableWidget, SIGNAL(cellActivated(int, int)), 
		this, SLOT(startFunction(int, int)));
 }

void SSMainMenu::roundCorner()
{
	QPixmap pixmap(size());
	QPainter painter(&pixmap);
	painter.fillRect(pixmap.rect(), Qt::white);
	painter.setBrush(Qt::black);
	//painter.drawRoundRect(pixmap.rect(), 10, 10);
	painter.drawRoundedRect(pixmap.rect(), 10, 10,Qt::RelativeSize);
	setMask(pixmap.createMaskFromColor(Qt::white));
}

