#include "StaffManagementUI.h"
#include "messagedef.h"
#include "Message.h"
#include "DUIHandler.h"

StaffManagementUI::StaffManagementUI()
{
	ui.setupUi(this);
	m_stuffDataModel = new QStandardItemModel(0, 3, this);
	m_sortProxyModel = new QSortFilterProxyModel;
	m_sortProxyModel->setDynamicSortFilter(true);

     ui.treeViewStaff->setRootIsDecorated(false);
     ui.treeViewStaff->setAlternatingRowColors(true);
     ui.treeViewStaff->setModel(m_sortProxyModel);
     ui.treeViewStaff->setSortingEnabled(true);

	 ui.comboBoxPattern->addItem(QString::fromLocal8Bit("正则表达式"), QRegExp::RegExp);
     ui.comboBoxPattern->addItem(QString::fromLocal8Bit("模糊匹配"), QRegExp::Wildcard);
	 ui.comboBoxPattern->addItem(QString::fromLocal8Bit("精确匹配"), QRegExp::FixedString);
}

StaffManagementUI::~StaffManagementUI()
{

}

void StaffManagementUI::OnEvent(Message & Msg){
	switch(Msg.type()) {
		case EVENT_STUFFMGNT:
		{
			show();
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
		default:
			break;
	}
}


void StaffManagementUI::on_pushButtonBack_clicked()
{

}

void StaffManagementUI::on_pushButtonLogoff_clicked()
{
//	m_handler->DeregisterObserver(this);
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
//	action->setData((byte*)NULL, 0);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::on_pushButtonExit_clicked()
{
	Message* action = new Message();
	action->setType(ACTION_EXIT);
//	action->setData((byte*)NULL, 0);
	m_uiHandler->StartAction(*action);
	delete action;
}