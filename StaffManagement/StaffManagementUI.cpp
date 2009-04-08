#include "StaffManagementUI.h"
#include "messagedef.h"
#include "Message.h"
#include "DUIHandler.h"
#include <QFont>

StaffManagementUI::StaffManagementUI()
{
	ui.setupUi(this);

	m_stuffDataModel = new QStandardItemModel(0, 6, this);
	m_stuffDataModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("员工编号"));
	m_stuffDataModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("姓名"));
	m_stuffDataModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("性别"));
	m_stuffDataModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("职务"));
	m_stuffDataModel->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("级别"));
	m_stuffDataModel->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("描述"));

	m_sortProxyModel = new QSortFilterProxyModel;
	m_sortProxyModel->setSourceModel(m_stuffDataModel);
	m_sortProxyModel->setDynamicSortFilter(true);
	m_sortProxyModel->setFilterKeyColumn(-1);

	SettingFont();

	ui.treeViewStaff->setRootIsDecorated(false);
	ui.treeViewStaff->setAlternatingRowColors(true);
	ui.treeViewStaff->setModel(m_sortProxyModel);
	ui.treeViewStaff->setSortingEnabled(true);
	ui.treeViewStaff->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.comboBoxPattern->addItem(QString::fromLocal8Bit("正则表达式"), QRegExp::RegExp);
	ui.comboBoxPattern->addItem(QString::fromLocal8Bit("模糊匹配"), QRegExp::Wildcard);
	ui.comboBoxPattern->addItem(QString::fromLocal8Bit("精确匹配"), QRegExp::FixedString);

	ui.comboBoxItem->addItem(QString::fromLocal8Bit("全部项目"));
	ui.comboBoxItem->addItem(QString::fromLocal8Bit("员工编号"));
	ui.comboBoxItem->addItem(QString::fromLocal8Bit("姓名"));
	ui.comboBoxItem->addItem(QString::fromLocal8Bit("性别"));
	ui.comboBoxItem->addItem(QString::fromLocal8Bit("职务"));
	ui.comboBoxItem->addItem(QString::fromLocal8Bit("级别"));
	ui.comboBoxItem->addItem(QString::fromLocal8Bit("描述"));

	connect(ui.lineEditKeyword, SIGNAL(textChanged(const QString &)), this, SLOT(filterRegExpChanged()));
	connect(ui.comboBoxPattern, SIGNAL(currentIndexChanged(int)),this, SLOT(filterRegExpChanged()));
	connect(ui.comboBoxItem, SIGNAL(currentIndexChanged(int)), this, SLOT(filterColumnChanged()));
	connect(ui.checkBoxSearch, SIGNAL(toggled(bool)), this, SLOT(filterRegExpChanged()));
	connect(ui.checkBoxSort, SIGNAL(toggled(bool)), this, SLOT(sortChanged()));
	//connect(ui.actionExport, SIGNAL(ui.actionExport->triggered)
	connect(ui.actionMenu, SIGNAL(triggered(bool)), this, SLOT(Menu()));
	connect(ui.actionLogOff, SIGNAL(triggered(bool)), this, SLOT(Logoff()));
	connect(ui.actionExit, SIGNAL(triggered(bool)), this, SLOT(Exit()));
}

StaffManagementUI::~StaffManagementUI()
{

}

void StaffManagementUI::OnEvent(Message & Msg){
	switch(Msg.type()) {
		case EVENT_STAFFMGNT:
		{
			if(isHidden())
				show();
			else
				this->setFocus();
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
		case EVENT_STAFFS:
		{
			addStaff((list<Staff>*)(Msg.data()));
		}
		default:
			break;
	}
}

void StaffManagementUI::Menu()
{
	Message* action = new Message();
	action->setType(ACTION_MAINMENU);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::Logoff()
{
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::Exit()
{
	Message* action = new Message();
	action->setType(ACTION_EXIT);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::showEvent ( QShowEvent * event )
{
//	switch(e->type()) {
//		case QEvent::Show:
//		{
				Message* action = new Message();
				action->setType(ACTION_GETSTAFF);
				m_uiHandler->StartAction(*action);
				delete action;
//		}
//	}
//	return true;
}

void StaffManagementUI::closeEvent ( QCloseEvent * event )
{
	int row = m_stuffDataModel->rowCount();
	m_stuffDataModel->removeRows(0 , row);
}

void StaffManagementUI::addStaff(list<Staff>* staff) 
{
	list<Staff>::iterator it = staff->begin();
	while(staff->end() != it) {
		m_stuffDataModel->insertRow(0);
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 0), QString::fromLocal8Bit(it->ID().c_str()));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 1), QString::fromLocal8Bit(it->Name().c_str()));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 2), it->Sex());
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 3), it->Type());
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 4), it->Level());
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 5), QString::fromLocal8Bit(it->Descrp().c_str()));
		it++;
	}
}

 void StaffManagementUI::filterRegExpChanged()
 {
     QRegExp::PatternSyntax syntax =
		 QRegExp::PatternSyntax(ui.comboBoxPattern->itemData(ui.comboBoxPattern->currentIndex()).toInt());
     Qt::CaseSensitivity caseSensitivity =
		 ui.checkBoxSearch->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

	 QRegExp regExp(ui.lineEditKeyword->text(), caseSensitivity, syntax);
     m_sortProxyModel->setFilterRegExp(regExp);
 }

 void StaffManagementUI::filterColumnChanged()
 {
	 m_sortProxyModel->setFilterKeyColumn(ui.comboBoxItem->currentIndex()-1);
 }

 void StaffManagementUI::sortChanged()
 {
     m_sortProxyModel->setSortCaseSensitivity( ui.checkBoxSort->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
 }

 void StaffManagementUI::SettingFont()
 {
	 QFont font = QFont("SimSun", 9);
	 ui.centralwidget->setFont(font);
	 ui.checkBoxSearch->setFont(font);
	 ui.checkBoxSort->setFont(font);
	 ui.comboBoxItem->setFont(font);
	 ui.comboBoxPattern->setFont(font);
	 ui.label->setFont(font);
	 ui.label_3->setFont(font);
	 ui.labelKeyword->setFont(font);
	 ui.layoutWidget->setFont(font);
	 ui.lineEditKeyword->setFont(font);
	 ui.menu_File->setFont(font);
	 ui.menubar->setFont(font);
	 ui.statusbar->setFont(font);
	 ui.treeViewStaff->setFont(font);
	 ui.groupBox->setFont(font);
	 font.setBold(true);
	 ui.treeViewStaff->header()->setFont(font);
 }