#include "StaffManagementUI.h"
#include "messagedef.h"
#include "Message.h"
#include "DUIHandler.h"
#include <QFont>
#include <QPoint>
#include "StaffDetail.h"
#include "Job.h"
#include "Level.h"
#include "Status.h"
#include "Staff.h"
#include "PasswordWidget.h"
#include "staffconfiguration.h"

//const char* StaffType[] = {"超级用户",  "老板", "店长", "收银员", "美发师", "洗发师", "美容师", "按摩师"};
//const char* StaffLevel[] = {"新手","熟练工","经验工","高级工","大师"};
const char* StaffSex[] = {"未知","男","女"};

StaffManagementUI::StaffManagementUI()
{
	setupUi();
	started = false;
	config = NULL;
	font = QFont("SimSun", 9);
//	setFont(font);
	SettingFont(font);

	m_stuffDataModel = new QStandardItemModel(0, 7, this);
	m_stuffDataModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("工号"));
	m_stuffDataModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("姓名"));
	m_stuffDataModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("性别"));
	m_stuffDataModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("职务"));
	m_stuffDataModel->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("级别"));
	m_stuffDataModel->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("状态"));
	m_stuffDataModel->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("手机"));

	m_sortProxyModel = new QSortFilterProxyModel;
	m_sortProxyModel->setSourceModel(m_stuffDataModel);
	m_sortProxyModel->setDynamicSortFilter(true);
	m_sortProxyModel->setFilterKeyColumn(-1);

	treeViewStaff->setModel(m_sortProxyModel);
	treeViewStaff->sortByColumn(0, Qt::AscendingOrder);
	comboBoxItem->setCurrentIndex(0);
	checkBoxSort->setChecked(true);
	checkBoxSearch->setChecked(true);

	connect(lineEditKeyword, SIGNAL(textChanged(const QString &)), this, SLOT(filterRegExpChanged()));
	connect(comboBoxPattern, SIGNAL(currentIndexChanged(int)),this, SLOT(filterRegExpChanged()));
	connect(comboBoxItem, SIGNAL(currentIndexChanged(int)), this, SLOT(filterColumnChanged()));
	connect(checkBoxSearch, SIGNAL(toggled(bool)), this, SLOT(filterRegExpChanged()));
	connect(checkBoxSort, SIGNAL(toggled(bool)), this, SLOT(sortChanged()));
	//connect(actionExport, SIGNAL(actionExport->triggered)
	connect(actionMenu, SIGNAL(triggered(bool)), this, SLOT(Menu()));
	connect(actionLogOff, SIGNAL(triggered(bool)), this, SLOT(Logoff()));
	connect(actionExit, SIGNAL(triggered(bool)), this, SLOT(Exit()));
	//	connect(actionStaffDetail, SIGNAL(triggered(bool)), this, SLOT(staffDetail()));
	connect(actionDeleteStaff, SIGNAL(triggered(bool)), this, SLOT(removeStaff()));
	connect(actionCasher4Client, SIGNAL(triggered(bool)), this, SLOT(cash4Client()));
	connect(treeViewStaff, SIGNAL(activated(const QModelIndex&)), this, SLOT(staffActivated(const QModelIndex&)));
	connect(treeViewStaff, SIGNAL(clicked(const QModelIndex&)), this, SLOT(staffActivated(const QModelIndex&)));
	connect(addPushButton, SIGNAL(clicked()), staffDetailWidget, SLOT(newStaff()));
	connect(deletePushButton, SIGNAL(clicked()), staffDetailWidget, SLOT(removeStaff()));
	connect(staffDetailWidget, SIGNAL(addedStaff(Staff*, QByteArray&)), this, SLOT(addStaff(Staff*, QByteArray&)));
	connect(staffDetailWidget, SIGNAL(modifiedStaff(Staff*, QByteArray&)), this, SLOT(modifyStaff(Staff*, QByteArray&)));
	connect(actionAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));
	connect(actionAboutQt, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(aboutQt()));
	connect(actionBrowseMyInfo, SIGNAL(triggered()), this, SLOT(browseMyInfo()));
	connect(actionChangeMyPassword, SIGNAL(triggered()), this, SLOT(changeMyPassword()));
	connect(actionStaffConfig, SIGNAL(triggered()), this, SLOT(staffConfig()));

//	actionBrowseMyRecords  = new QAction(this);;
//	actionBrowseMySalary = new QAction(this);
//	 = new QAction(this);
//	 = new QAction(this);
//	actionAboutQt = new QAction(this);
//	actionAboutCosmetic = new QAction(this);
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
		case EVENT_ALLSTAFF:
		{
			addStaff((list<Staff>*)(Msg.data()));
			break;
		}
		case EVENT_STAFFADDED:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->browseStaff(static_cast<Staff*>(Msg.data()));
				getAllStaff();
			} else {
				showMessageBox(QMessageBox::Critical, addStaffError);
			}
			break;
		}
		case EVENT_STAFFREMOVED:
		{
			if(NULL != Msg.data()) {
				getAllStaff();
			} else {
				showMessageBox(QMessageBox::Critical, removeStaffError);
			}
			break;
		}
		case EVENT_STAFFMODIFIED:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->browseStaff(static_cast<Staff*>(Msg.data()));
				getAllStaff();
			} else {
				showMessageBox(QMessageBox::Critical, modifyStaffError);
			}
			break;
		}
		case EVENT_STAFF:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->browseStaff(static_cast<Staff*>(Msg.data()));
			} else {

			}
			break;

		}
		case EVENT_GETPICTURE:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->displayPic(*static_cast<QByteArray*>(Msg.data()));
			} else {

			}
			break;

		}

		case EVENT_LOGGEDSTAFF:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->browseStaff(static_cast<Staff*>(Msg.data()), 1);
			} else {

			}
			break;

		}
		case EVENT_JOBTYPE:
		{	
			m_staffType.clear();
			list<Job>* jobs = static_cast<list<Job>*>(Msg.data());
			staffDetailWidget->setJob(jobs);
			if(NULL != config)
				config->ui.pageJob->pushjobs(jobs);
			for(list<Job>::iterator it = jobs->begin() ; it != jobs->end() ; it++) {
				m_staffType[it->id()] = *it;
			}
			break;
		}
		case EVENT_LEVELTYPE: 
		{
			m_staffLevel.clear();
			list<Level>* levels = static_cast<list<Level>*>(Msg.data());
			staffDetailWidget->setLevel(levels);
			if(NULL != config)
				config->ui.pageLevel->pushLevels(levels);
			for(list<Level>::iterator it = levels->begin() ; it != levels->end() ; it++) {
				m_staffLevel[it->id()] = *it;
			}
			break;
		}
		case EVENT_STATUSTYPE: 
		{
			m_staffState.clear();
			list<Status>* status = static_cast<list<Status>*>(Msg.data());
			staffDetailWidget->setStatus(status);
			for(list<Status>::iterator it = status->begin() ; it != status->end() ; it++) {
				m_staffState[it->id()] = *it;
			}
			break;
		}
		case EVENT_SETJOBTYPE:
		{
			list<Job>* error = static_cast<list<Job>*>(Msg.data());
			getJobType();
			if(!error->empty()){
				string errorstr = "职务";
				for(list<Job>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += "“";
					errorstr += it->name();
					errorstr += "”";
				}
				errorstr += "未能成功修改，请重试。";
				showMessageBox(QMessageBox::Warning, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_SETLEVELTYPE:
		{
			list<Level>* error = static_cast<list<Level>*>(Msg.data());
			getLevelType();
			if(!error->empty()){
				string errorstr = "等级";
				for(list<Level>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += "“";
					errorstr += it->name();
					errorstr += "”";
				}
				errorstr += "未能成功修改，请重试。";
				showMessageBox(QMessageBox::Warning, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_REMOVEJOBTYPE:
		{
			list<Job>* error = static_cast<list<Job>*>(Msg.data());
			getJobType();
			if(!error->empty()){
				string errorstr = "职务";
				for(list<Job>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += "“";
					errorstr += it->name();
					errorstr += "”";
				}
				errorstr += "未能成功删除，可能是还有员工被设置为该职务。";
				showMessageBox(QMessageBox::Warning, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_REMOVELEVELTYPE:
		{
			list<Level>* error = static_cast<list<Level>*>(Msg.data());
			getLevelType();
			if(!error->empty()){
				string errorstr = "等级";
				for(list<Level>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += "“";
					errorstr += it->name();
					errorstr += "”";
				}
				errorstr += "未能成功删除，可能是还有员工被设置为该等级。";
				showMessageBox(QMessageBox::Warning, errorstr);
			}
			delete error;
			break;
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

bool StaffManagementUI::eventFilter(QObject * obj, QEvent * ev)
{	
	if(treeViewStaff == obj) {
		switch(ev->type()) {
			case QEvent::ContextMenu:
			{
				QMenu menu(treeViewStaff);
				menu.addAction(actionStaffDetail);
				menu.addAction(actionDeleteStaff);
				menu.addAction(actionCasher4Client);
				menu.setFont(font);
				menu.exec(dynamic_cast<QContextMenuEvent*>(ev)->globalPos());
				return true;
				break;
			}
		}
	}
	return QMainWindow::eventFilter(obj, ev);
}

bool StaffManagementUI::event(QEvent * ev)
{

	switch(ev->type()) {
		case QEvent::Show:
		{
			if(!started) {
				started = true;
				getJobType();
				getLevelType();
				getStatusType();
				getAllStaff();
			}
			break;
		}
		case QEvent::ContextMenu:
		{
			QMenu menu(this);
			menu.addAction(actionMenu);
			menu.addAction(actionLogOff);
			menu.addAction(actionExit);
			menu.setFont(font);
			QPoint pos = dynamic_cast<QContextMenuEvent*>(ev)->globalPos();
			menu.exec(pos);
			break;
		}
	}
	return QMainWindow::event(ev);
}

void StaffManagementUI::addStaff(list<Staff>* staff) 
{
	list<Staff>::iterator it = staff->begin();
	while(staff->end() != it) {
		m_stuffDataModel->insertRow(0);
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 0), it->ID());
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 1), QString::fromLocal8Bit(it->Name().c_str()));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 2), QString::fromLocal8Bit(StaffSex[it->Sex()]));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 3), QString::fromLocal8Bit(m_staffType[it->Type()].name().c_str()));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 4), QString::fromLocal8Bit(m_staffLevel[it->Level()].name().c_str()));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 5), QString::fromLocal8Bit(m_staffState[it->status()].name().c_str()));
		m_stuffDataModel->setData(m_stuffDataModel->index(0, 6), QString::fromLocal8Bit(it->cell().c_str()));
		it++;
	}
}

 void StaffManagementUI::filterRegExpChanged()
 {
     QRegExp::PatternSyntax syntax =
		 QRegExp::PatternSyntax(comboBoxPattern->itemData(comboBoxPattern->currentIndex()).toInt());
     Qt::CaseSensitivity caseSensitivity =
		 checkBoxSearch->isChecked() ? Qt::CaseInsensitive : Qt::CaseSensitive;

	 QRegExp regExp(lineEditKeyword->text(), caseSensitivity, syntax);
     m_sortProxyModel->setFilterRegExp(regExp);
 }

 void StaffManagementUI::filterColumnChanged()
 {
	 m_sortProxyModel->setFilterKeyColumn(comboBoxItem->currentIndex()-1);
 }

 void StaffManagementUI::sortChanged()
 {
     m_sortProxyModel->setSortCaseSensitivity( checkBoxSort->isChecked() ? Qt::CaseInsensitive : Qt::CaseSensitive);
 }

void StaffManagementUI::staffActivated(const QModelIndex& item)
{
	QModelIndex currentIndex = item.sibling(item.row(), 0);
	staffDetail(currentIndex.data().toUInt());
}

void StaffManagementUI::staffDetail(uint32 id) {
	uint32* staffid = new uint32(id);
	uint32* staffid2 = new uint32(id);
	Message* action = new Message(ACTION_GETSTAFF, staffid);
	m_uiHandler->StartAction(*action);
	delete action;
	Message* action2 = new Message(ACTION_GETPICTURE, staffid2);
	m_uiHandler->StartAction(*action2);
	delete action2;
}
void StaffManagementUI::getJobType() {
	Message* action = new Message();
	action->setType(ACTION_GETJOBTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}
void StaffManagementUI::getLevelType() {
	Message* action = new Message();
	action->setType(ACTION_GETLEVELTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::getStatusType() {
	Message* action = new Message();
	action->setType(ACTION_GETSTATUSTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::removeStaff()	
{
	QModelIndex currentIndex = treeViewStaff->currentIndex().sibling(treeViewStaff->currentIndex().row(), 0);
	QModelIndex nameIndex = treeViewStaff->currentIndex().sibling(treeViewStaff->currentIndex().row(), 1);
	removeStaff(currentIndex.data().toUInt(), nameIndex.data().toString().toLocal8Bit().data());
}

void StaffManagementUI::removeStaff(uint32 id, string name)	
{
	QString confirm =QString::fromLocal8Bit(removeStaffConfirm).arg(QString::fromLocal8Bit(name.c_str()));
	if(QMessageBox::No == showMessageBox(QMessageBox::Question, confirm.toLocal8Bit().data())) return;
	uint32* staffid = new uint32(id);
	Message* action = new Message();
	action->setType(ACTION_REMOVESTAFF);
	action->setData(staffid);
	m_uiHandler->StartAction(*action);
	delete action;
}


void StaffManagementUI::cash4Client()
{

}
void StaffManagementUI::getAllStaff()
{
	m_stuffDataModel->removeRows(0, m_stuffDataModel->rowCount());
	Message* action = new Message();
	action->setType(ACTION_GEALLSTAFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffManagementUI::addStaff(Staff* staff, QByteArray& data)
{
	if(staff->Name().empty()) {
		showMessageBox(QMessageBox::Warning, emptyNameWarnning);
		return;
	}
	Message* action = new Message(ACTION_ADDSTAFF, staff);
	if(!data.isEmpty())
		action->setData2(&data);
	m_uiHandler->StartAction(*action);
	delete action;

}
void StaffManagementUI::modifyStaff(Staff* staff, QByteArray& data)
{
	if(staff->Name().empty()) {
		showMessageBox(QMessageBox::Warning, emptyNameWarnning);
		return;
	}
	Message* action = new Message(ACTION_MODIFYSTAFF, staff);
	if(!data.isEmpty())
		action->setData2(&data);
	m_uiHandler->StartAction(*action);
	delete action;

}

 void StaffManagementUI::browseMyInfo()
 {
 	Message* action = new Message();
	action->setType(ACTION_GETLOGGEDSTAFF);
	m_uiHandler->StartAction(*action);
	delete action;
}
 
void StaffManagementUI::changeMyPassword()
{
	PasswordWidget* passwordWindow = new PasswordWidget(this);
	connect(passwordWindow, SIGNAL(submitPassword(string, string)), this, SLOT(changePasswrod(string, string)));
	passwordWindow->show();
}

void StaffManagementUI::changePasswrod(string oldpw, string newpw)
{
	list<string>* pwList = new list<string>;
	pwList->push_back(oldpw);
	pwList->push_back(newpw);
	Message* action = new Message(ACTION_CHANGEPASSWORD, pwList);
	m_uiHandler->StartAction(*action);
	delete action;
}

 void StaffManagementUI::staffConfig()
 {
 	config = new StaffConfiguration(this);
	getJobType();
	getLevelType();
	getStatusType();
	connect(config->ui.pageJob, SIGNAL(submitted(list<Job>*)), this, SLOT(setJobs(list<Job>*)));
	connect(config->ui.pageLevel, SIGNAL(submitted(list<Level>*)), this, SLOT(setLevels(list<Level>*)));
	config->show();
 }

 void StaffManagementUI::setLevels(list<Level>* levels) 
 {
 	Message* action = new Message(ACTION_SETLEVELTYPE, levels);
	m_uiHandler->StartAction(*action);
	delete action;
 }

void StaffManagementUI::setJobs(list<Job>* jobs)
{
	 Message* action = new Message(ACTION_SETJOBTYPE, jobs);
	m_uiHandler->StartAction(*action);
	delete action;
}

 void StaffManagementUI::SettingFont(QFont& font)
 {
	font.setBold(true);
	treeViewStaff->header()->setFont(font);
	staffGroupBox->setFont(font);
	optionGroupBox->setFont(font);
	infoGroupBox->setFont(font);

	font.setBold(false);
	checkBoxSearch->setFont(font);
	checkBoxSort->setFont(font);
	comboBoxItem->setFont(font);
	comboBoxPattern->setFont(font);
	labelSearchItem->setFont(font);
	labelSearchPattern->setFont(font);
	labelKeyword->setFont(font);
	lineEditKeyword->setFont(font);
	menu_File->setFont(font);
	menu_About->setFont(font);
	menu_Personal->setFont(font);
	menu_Setting->setFont(font);
	menubar->setFont(font);
	statusbar->setFont(font);
	treeViewStaff->setFont(font);
	staffDetailWidget->SettingFont(font);
	statusbar->setFont(font);
	deletePushButton->setFont(font);
	addPushButton->setFont(font);
	seletCheckBox->setFont(font);
	messageBox->setFont(font);

 }

void StaffManagementUI::setupUi() {
	setMouseTracking(true);

	messageBox = new QMessageBox(this);
	messageBox->setWindowTitle(QString::fromLocal8Bit("员工管理"));

	customCentralWidget = new QWidget(this);
	customCentralWidget->setMouseTracking(true);

	staffGroupBox = new QGroupBox(QString::fromLocal8Bit("员工浏览"), customCentralWidget);
	QBoxLayout* staffLayout = new QBoxLayout(QBoxLayout::LeftToRight, staffGroupBox);
	staffGroupBox->setMouseTracking(true);
	treeViewStaff = new QTreeView(staffGroupBox);
	staffLayout->addWidget(treeViewStaff);
	staffGroupBox->setLayout(staffLayout);
	treeViewStaff->setMouseTracking(true);
	treeViewStaff->setRootIsDecorated(false);
	treeViewStaff->setAlternatingRowColors(true);
	treeViewStaff->setSortingEnabled(true);
	treeViewStaff->setEditTriggers(QAbstractItemView::NoEditTriggers);
	treeViewStaff->setContextMenuPolicy(Qt::DefaultContextMenu);
	treeViewStaff->installEventFilter(this);

	infoGroupBox = new QGroupBox(QString::fromLocal8Bit("员工资料"), customCentralWidget);
	QBoxLayout* infoLayout = new QBoxLayout(QBoxLayout::LeftToRight, infoGroupBox);
	staffDetailWidget = new StaffDetail(infoGroupBox, SINFO_BROWSE);
	infoLayout->addWidget(staffDetailWidget);
	infoGroupBox->setLayout(infoLayout);


	optionGroupBox = new QGroupBox(QString::fromLocal8Bit("操作"), customCentralWidget);
	comboBoxPattern = new QComboBox(optionGroupBox);
	labelSearchPattern = new QLabel(QString::fromLocal8Bit("匹配方式(&P)"), optionGroupBox);
	labelSearchPattern->setBuddy(comboBoxPattern);
	comboBoxPattern->addItem(QString::fromLocal8Bit("正则表达式"), QRegExp::RegExp);
	comboBoxPattern->addItem(QString::fromLocal8Bit("模糊匹配"), QRegExp::Wildcard);
	comboBoxPattern->addItem(QString::fromLocal8Bit("精确匹配"), QRegExp::FixedString);

	lineEditKeyword = new QLineEdit(optionGroupBox);
	labelKeyword = new QLabel(QString::fromLocal8Bit("关键词(&K)"), optionGroupBox);
	labelKeyword->setBuddy(lineEditKeyword);

	comboBoxItem = new QComboBox(optionGroupBox);
	labelSearchItem = new QLabel(QString::fromLocal8Bit("搜索项(&I)"), optionGroupBox);
	labelSearchItem->setBuddy(comboBoxItem);
	comboBoxItem->addItem(QString::fromLocal8Bit("全部项目"));
	comboBoxItem->addItem(QString::fromLocal8Bit("员工编号"));
	comboBoxItem->addItem(QString::fromLocal8Bit("姓名"));
	comboBoxItem->addItem(QString::fromLocal8Bit("性别"));
	comboBoxItem->addItem(QString::fromLocal8Bit("职务"));
	comboBoxItem->addItem(QString::fromLocal8Bit("级别"));
	comboBoxItem->addItem(QString::fromLocal8Bit("描述"));

	checkBoxSort = new QCheckBox(QString::fromLocal8Bit("排序忽略大小写(&N)"), optionGroupBox);
	checkBoxSearch = new QCheckBox(QString::fromLocal8Bit("搜索忽略大小写(&M)"), optionGroupBox);
	deletePushButton = new QPushButton(QString::fromLocal8Bit("删除员工(&R)"), optionGroupBox);
    addPushButton = new QPushButton(QString::fromLocal8Bit("添加员工(&T)"), optionGroupBox);
    seletCheckBox = new QCheckBox(QString::fromLocal8Bit("全选(&A)"), optionGroupBox);
	deletePushButton->setMinimumHeight(30);
	addPushButton->setMinimumHeight(30);
	deletePushButton->setMaximumHeight(50);
	addPushButton->setMaximumHeight(50);
	deletePushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	addPushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


//	actionExport = new QAction(this);
	actionMenu = new QAction(this);
	actionLogOff = new QAction(this);
	actionExit = new QAction(this);
	actionStaffDetail = new QAction(this); 
	actionDeleteStaff = new QAction(this);
	actionCasher4Client = new QAction(this);
	actionBrowseMyInfo = new QAction(this);
	actionBrowseMyRecords  = new QAction(this);;
	actionBrowseMySalary = new QAction(this);
	actionChangeMyPassword = new QAction(this);
	actionStaffConfig = new QAction(this);
	actionAboutQt = new QAction(this);
	actionAboutCosmetic = new QAction(this);

	menubar = new QMenuBar(this);
	menu_File = new QMenu(QString::fromLocal8Bit("文件(&F)"), menubar);
	menu_Personal = new QMenu(QString::fromLocal8Bit("个人信息(&P)"), menubar);
	menu_Setting = new QMenu(QString::fromLocal8Bit("员工属性(&D)"), menubar);
	menu_About = new QMenu(QString::fromLocal8Bit("关于(&A)"), menubar);
	setMenuBar(menubar);


	menubar->addAction(menu_File->menuAction());
//	menu_File->addSeparator();
//	menu_File->addAction(actionExport);
//	menu_File->addSeparator();
	menu_File->addAction(actionMenu);
	menu_File->addAction(actionLogOff);
	menu_File->addAction(actionExit);
	menu_Personal->addAction(actionBrowseMyInfo);
	menu_Personal->addAction(actionBrowseMyRecords);
	menu_Personal->addAction(actionBrowseMySalary);
	menu_Personal->addAction(actionChangeMyPassword);
	menu_Setting->addAction(actionStaffConfig);
	menu_About->addAction(actionAboutCosmetic);
	menu_About->addAction(actionAboutQt);
//	actionExport->setText(QString::fromLocal8Bit("导出(&E)"));
	actionMenu->setText(QString::fromLocal8Bit("主菜单(&M)"));
	actionLogOff->setText(QString::fromLocal8Bit("注销(&L)"));
	actionExit->setText(QString::fromLocal8Bit("退出(&X)"));
	menu_File->setTitle(QString::fromLocal8Bit("文件(&F)"));
	actionStaffDetail->setText(QString::fromLocal8Bit("详情及业绩(&D)"));
	actionDeleteStaff->setText(QString::fromLocal8Bit("删除员工(&R)"));
	actionCasher4Client->setText(QString::fromLocal8Bit("为客户储值(&C)"));
	actionBrowseMyInfo->setText(QString::fromLocal8Bit("基本信息(&B)"));
	actionBrowseMyRecords->setText(QString::fromLocal8Bit("业绩(&A)"));
	actionBrowseMySalary->setText(QString::fromLocal8Bit("工资(&S)"));
	actionChangeMyPassword->setText(QString::fromLocal8Bit("更改密码(&M)"));
	actionStaffConfig->setText(QString::fromLocal8Bit("员工属性(&X)"));
	actionAboutQt->setText(QString::fromLocal8Bit("关于Qt(&C)"));
	actionAboutCosmetic->setText(QString::fromLocal8Bit("关于科思美(&C)"));

	menubar->addAction(menu_Personal->menuAction());
	menubar->addAction(menu_Setting->menuAction());
	menubar->addAction(menu_About->menuAction());


	statusbar = new QStatusBar(this);
	setStatusBar(statusbar);

	QHBoxLayout *optinonButtonlayout = new QHBoxLayout();
	optinonButtonlayout->addWidget(seletCheckBox, 1);
	optinonButtonlayout->addWidget(deletePushButton, 10);
	optinonButtonlayout->addWidget(addPushButton, 10);

	QGridLayout *optionLayout = new QGridLayout(optionGroupBox);
	optionLayout->addWidget(labelKeyword, 0, 0 ,1 ,1);
	optionLayout->addWidget(lineEditKeyword, 0, 1, 1, 2);
	optionLayout->addWidget(labelSearchPattern, 1, 0, 1, 1);
	optionLayout->addWidget(comboBoxPattern, 1, 1, 1, 2);
	optionLayout->addWidget(labelSearchItem, 2, 0, 1, 1);
	optionLayout->addWidget(comboBoxItem, 2, 1, 1, 2);
	optionLayout->addWidget(checkBoxSearch, 3, 0, 1, 2);
	optionLayout->addWidget(checkBoxSort, 3, 2);
	optionLayout->addLayout(optinonButtonlayout, 4 , 0, 1, 3);
	optionLayout->setRowStretch(4, 1);
	optionGroupBox->setLayout(optionLayout);

	QVBoxLayout *rightLayout = new QVBoxLayout();
	rightLayout->addWidget(infoGroupBox, 2);
	rightLayout->addWidget(optionGroupBox, 1);


	QHBoxLayout *mainLayout = new QHBoxLayout(customCentralWidget);
	mainLayout->addWidget(staffGroupBox, 10);
	mainLayout->addLayout(rightLayout, 1);
	mainLayout->setMargin(2);


	customCentralWidget->setLayout(mainLayout);
	setCentralWidget(customCentralWidget);
	setWindowTitle(QString::fromLocal8Bit("员工管理"));
	this->setWindowIcon(QIcon(":/staff/Resources/people.png"));

	resize(800, 600);
 }

  QMessageBox::StandardButton StaffManagementUI::showMessageBox(QMessageBox::Icon icon, string title, string info) {
	messageBox->setIcon(icon);
	messageBox->setText(QString::fromLocal8Bit(title.c_str()));
	messageBox->setInformativeText(QString::fromLocal8Bit(info.c_str()));
	if(QMessageBox::Information == icon) {
		messageBox->setStandardButtons(QMessageBox::Ok);
		 messageBox->setDefaultButton(QMessageBox::Ok);
	}
	if(QMessageBox::Question == icon) {
		messageBox->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
		 messageBox->setDefaultButton(QMessageBox::No);
	}
	return (QMessageBox::StandardButton)messageBox->exec();
 }
