#include "StuffManagement.h"
#include "Message.h"
#include "IActionHandler.h"

StuffManagement::StuffManagement()
{
	ui.setupUi(this);
	m_stuffDataModel = new QStandardItemModel(0, 3, this);
	m_sortProxyModel = new QSortFilterProxyModel;
	m_sortProxyModel->setDynamicSortFilter(true);

     ui.treeViewStuff->setRootIsDecorated(false);
     ui.treeViewStuff->setAlternatingRowColors(true);
     ui.treeViewStuff->setModel(m_sortProxyModel);
     ui.treeViewStuff->setSortingEnabled(true);

	 ui.comboBoxPattern->addItem(QString::fromLocal8Bit("正则表达式"), QRegExp::RegExp);
     ui.comboBoxPattern->addItem(QString::fromLocal8Bit("模糊匹配"), QRegExp::Wildcard);
	 ui.comboBoxPattern->addItem(QString::fromLocal8Bit("精确匹配"), QRegExp::FixedString);
}

StuffManagement::~StuffManagement()
{

}

void StuffManagement::OnEvent(Message & Msg){
	switch(Msg.type()) {
		case EVENT_STUFFMGNT:
		{
			show();
			break;
		}
		case EVENT_LOGGEDOFF:
		{
//			m_handler->DeregisterObserver(this);
			close();
			break;
		}
		case EVENT_EXIT:
		{
			close();
			break;
		}
		default:
			break;
	}
}


void StuffManagement::on_pushButtonBack_clicked()
{

}

void StuffManagement::on_pushButtonLogoff_clicked()
{
//	m_handler->DeregisterObserver(this);
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
//	action->setData((byte*)NULL, 0);
	m_handler->StartAction(*action);
	delete action;
}

void StuffManagement::on_pushButtonExit_clicked()
{
	Message* action = new Message();
	action->setType(ACTION_EXIT);
//	action->setData((byte*)NULL, 0);
	m_handler->StartAction(*action);
	delete action;
}