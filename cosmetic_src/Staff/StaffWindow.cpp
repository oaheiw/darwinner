#include "StaffWindow.h"
#include "messagedef.h"
#include "Message.h"
#include "DUIHandler.h"
#include <QPoint>
#include "StaffDetail.h"
#include "Job.h"
#include "Level.h"
#include "Status.h"
#include "Staff.h"
#include "MessageBox.h"
#include "PasswordWidget.h"
#include "staffconfiguration.h"
#include "SearchBox.h"

StaffWindow::StaffWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.itemView->installEventFilter(this);
	ui.menuBar->installEventFilter(this);
	ui.mainToolBar->installEventFilter(this);

	started = false;
	config = NULL;
	staffDetailWidget = new StaffDetail(this);
	m_searchBox = new SearchBox(this);
	m_searchBox->addFilterItem(QString::fromLocal8Bit("工号"));
	m_searchBox->addFilterItem(QString::fromLocal8Bit("姓名"));
	m_searchBox->addFilterItem(QString::fromLocal8Bit("性别"));
	m_searchBox->addFilterItem(QString::fromLocal8Bit("职务"));
	m_searchBox->addFilterItem(QString::fromLocal8Bit("级别"));
	m_searchBox->addFilterItem(QString::fromLocal8Bit("状态"));
	m_searchBox->addFilterItem(QString::fromLocal8Bit("手机"));
	
	ui.sideBar->addWidget(staffDetailWidget, 0, 0);
	ui.sideBar->addWidget(m_searchBox, 1, 0);
	
	ui.itemView->init(7);
	ui.itemView->setHeaderData(0, QString::fromLocal8Bit("工号"));
	ui.itemView->setHeaderData(1, QString::fromLocal8Bit("姓名"));
	ui.itemView->setHeaderData(2, QString::fromLocal8Bit("性别"));
	ui.itemView->setHeaderData(3, QString::fromLocal8Bit("职务"));
	ui.itemView->setHeaderData(4, QString::fromLocal8Bit("级别"));
	ui.itemView->setHeaderData(5, QString::fromLocal8Bit("状态"));
	ui.itemView->setHeaderData(6, QString::fromLocal8Bit("手机"));

	connect(m_searchBox, SIGNAL(regExpChanged(QRegExp &)), ui.itemView, SLOT(changeRegExp(QRegExp &)));
	connect(m_searchBox, SIGNAL(columnChanged(int)), ui.itemView, SLOT(changeFilterColumn(int)));
	connect(m_searchBox, SIGNAL(sortChanged(int)), ui.itemView, SLOT(changeSortCase(int)));

	connect(staffDetailWidget, SIGNAL(addedStaff(Staff*, QByteArray&)), this, SLOT(addStaff(Staff*, QByteArray&)));
	connect(staffDetailWidget, SIGNAL(modifiedStaff(Staff*, QByteArray&)), this, SLOT(modifyStaff(Staff*, QByteArray&)));

	connect(ui.itemView, SIGNAL(itemActivated(int, int, QVariant &)), this, SLOT(staffActivated(int, int, QVariant &)));
}

StaffWindow::~StaffWindow()
{

}

void StaffWindow::dealAction(QAction* action)
{
	if(action == ui.actionMenu) { Menu(); return; }
	if(action == ui.actionLogOff) { Logoff(); return; }
	if(action == ui.actionExit) { Exit(); return; }
	if(action == ui.actionRemoveStaff) { removeStaff(); return; }
	if(action == ui.actionAddStaff) { staffDetailWidget->newStaff(); return; }
	if(action == ui.actionEditStaff) { staffDetailWidget->modify(); return; }
	if(action == ui.actionBrowseMyInfo) { browseMyInfo(); return; }
	if(action == ui.actionStaffConfig) { staffConfig(); return; }
	if(action == ui.actionChangeMyPassword) { changeMyPassword(); return; }
	if(action == ui.actionAboutCosmetic) { TOBE_REALIZIED; return; }
	if(action == ui.actionBrowseMyRecords) { TOBE_REALIZIED; return; }
	if(action == ui.actionBrowseMySalary) { TOBE_REALIZIED; return; }
	if(action == ui.actionLock) { TOBE_REALIZIED; return; }
	if(action == ui.actionRights) { TOBE_REALIZIED; return; }
	if(action == ui.actionSmallIcon) { showSmallIcon(ui.actionSmallIcon->isChecked()); return; }
	if(action == ui.actionTextLabel) { showTextLabel(ui.actionTextLabel->isChecked()); return; }
	if(action == ui.actionToolBar) { showToolBar(ui.actionToolBar->isChecked()); return; }
}

void StaffWindow::OnEvent(Message & Msg){
	switch(Msg.type()) {
		case EVENT_STAFFMGNT:
		{
			if(isHidden())
				show();
			else
				setFocus();
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
				if(NULL != Msg.data2()) {
					QByteArray* image = static_cast<QByteArray*>(Msg.data2());
					staffDetailWidget->displayPic(*image);
					delete image;
				}
				getAllStaff();
			} else {
				MessageBox::showMessageBox(this, QMessageBox::Critical, smWindowTitle, addStaffError);
			}
			break;
		}
		case EVENT_STAFFREMOVED:
		{
			if(NULL != Msg.data()) {
				Staff* emptyStaff = new Staff;
				emptyStaff->clear();
				staffDetailWidget->browseStaff(emptyStaff);
				delete emptyStaff;
				getAllStaff();
			} else {
				MessageBox::showMessageBox(this, QMessageBox::Critical, smWindowTitle, removeStaffError);
			}
			break;
		}
		case EVENT_STAFFMODIFIED:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->browseStaff(static_cast<Staff*>(Msg.data()));
				if(NULL != Msg.data2()) {
					QByteArray* image = static_cast<QByteArray*>(Msg.data2());
					staffDetailWidget->displayPic(*image);
					delete image;
				}
				getAllStaff();
			} else {
				MessageBox::showMessageBox(this, QMessageBox::Critical, smWindowTitle, modifyStaffError);
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
				QByteArray* image = static_cast<QByteArray*>(Msg.data());
				staffDetailWidget->displayPic(*image);
				delete image;
			} else {

			}
			break;

		}

		case EVENT_LOGGEDSTAFF:
		{
			if(NULL != Msg.data()) {
				staffDetailWidget->browseStaff(static_cast<Staff*>(Msg.data()), 1);
				if(NULL != Msg.data2())
					staffDetailWidget->displayPic(*static_cast<QByteArray*>(Msg.data2()));
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
				string errorstr = jobString;
				for(list<Job>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += leftMark;
					errorstr += it->name();
					errorstr += rightMark;
				}
				errorstr += modifyWaring;
				MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_SETLEVELTYPE:
		{
			list<Level>* error = static_cast<list<Level>*>(Msg.data());
			getLevelType();
			if(!error->empty()){
				string errorstr = levelString;
				for(list<Level>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += leftMark;
					errorstr += it->name();
					errorstr += rightMark;
				}
				errorstr += modifyWaring;
				MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_REMOVEJOBTYPE:
		{
			list<Job>* error = static_cast<list<Job>*>(Msg.data());
			getJobType();
			if(!error->empty()){
				string errorstr = jobString;
				for(list<Job>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += "“";
					errorstr += it->name();
					errorstr += "”";
				}
				errorstr += levelRemoveWarning;
				MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_REMOVELEVELTYPE:
		{
			list<Level>* error = static_cast<list<Level>*>(Msg.data());
			getLevelType();
			if(!error->empty()){
				string errorstr = levelString;
				for(list<Level>::iterator it = error->begin() ; it != error->end() ; it++) {
					errorstr += "“";
					errorstr += it->name();
					errorstr += "”";
				}
				errorstr += levelRemoveWarning;
				MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, errorstr);
			}
			delete error;
			break;
		}
		case EVENT_CHANGEPASSWORD:
		{
			int* r = static_cast<int*>(Msg.data());
			if(ERROR_NO_ERROR == *r) {
				MessageBox::showMessageBox(this, QMessageBox::Information, smWindowTitle, changePwSucces);
			}
			else if(ERROR_PASSWORD_WRONG == *r || ERROR_DBERROR == *r) {
				MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, changePwFailure);
			}
			delete r;
			break;
		}
		default:
			break;
	}
}

void StaffWindow::Menu()
{
	Message* action = new Message();
	action->setType(ACTION_MAINMENU);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::Logoff()
{
	Message* action = new Message();
	action->setType(ACTION_LOGOFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::Exit()
{
	Message* action = new Message();
	action->setType(ACTION_EXIT);
	m_uiHandler->StartAction(*action);
	delete action;
}

bool StaffWindow::eventFilter(QObject * obj, QEvent * ev)
{	
	switch(ev->type()) {
		case QEvent::ContextMenu:
		{
			QMenu menu(this);
			if(ui.itemView == obj) {
				menu.addAction(ui.actionRemoveStaff);
			}
			if(ui.mainToolBar == obj || ui.menuBar == obj) {
				QMenu menuBarMenu(this);
				menu.addAction(ui.actionSmallIcon);
				menu.addAction(ui.actionTextLabel);
				menu.addAction(ui.actionToolBar);
			}
			menu.exec(dynamic_cast<QContextMenuEvent*>(ev)->globalPos());
			ev->accept();
			return true;
			break;
		}
	}
	return QMainWindow::eventFilter(obj, ev);
}

bool StaffWindow::event(QEvent * ev)
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
				showMaximized(); 
			}
			break;
		}
		case QEvent::ContextMenu:
		{
			QMenu mainMenu(this);
			mainMenu.addAction(ui.actionMenu);
			mainMenu.addAction(ui.actionLock);
			mainMenu.addAction(ui.actionLogOff);
			mainMenu.addAction(ui.actionExit);
			mainMenu.exec(dynamic_cast<QContextMenuEvent*>(ev)->globalPos());
			ev->accept();
			return true;
			break;
		}
	}
	return QMainWindow::event(ev);
}

void StaffWindow::addStaff(list<Staff>* staff) 
{
	list<Staff>::iterator it = staff->begin();
	int row = 0;
	while(staff->end() != it) {
		ui.itemView->addData(row, 0, it->ID());
		ui.itemView->addData(row, 1, QString::fromLocal8Bit(it->Name().c_str()));
		ui.itemView->addData(row, 2, QString::fromLocal8Bit(StaffSex[it->Sex()]));
		ui.itemView->addData(row, 3, QString::fromLocal8Bit(m_staffType[it->Type()].name().c_str()));
		ui.itemView->addData(row, 4, QString::fromLocal8Bit(m_staffLevel[it->Level()].name().c_str()));
		ui.itemView->addData(row, 5, QString::fromLocal8Bit(m_staffState[it->status()].name().c_str()));
		ui.itemView->addData(row, 6, QString::fromLocal8Bit(it->cell().c_str()));
		row++;
		it++;
	}
}

void StaffWindow::staffActivated(int row, int column, QVariant & data)
{
	staffDetail(ui.itemView->sibling(row, 0).toUInt());
}

void StaffWindow::staffDetail(uint32 id) {
	uint32* staffid = new uint32(id);
	uint32* staffid2 = new uint32(id);
	Message* action = new Message(ACTION_GETSTAFF, staffid);
	m_uiHandler->StartAction(*action);
	delete action;
	Message* action2 = new Message(ACTION_GETPICTURE, staffid2);
	m_uiHandler->StartAction(*action2);
	delete action2;
}

void StaffWindow::getJobType() {
	Message* action = new Message();
	action->setType(ACTION_GETJOBTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::getLevelType() {
	Message* action = new Message();
	action->setType(ACTION_GETLEVELTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::getStatusType() {
	Message* action = new Message();
	action->setType(ACTION_GETSTATUSTYPE);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::removeStaff()	
{
	int row = 0;
	int col = 0;
	ui.itemView->currentIndex(row, col);
	uint32 currentStaffID = ui.itemView->sibling(row, 0).toUInt();
	string  currentStaffName = string(ui.itemView->sibling(row, 1).toString().toLocal8Bit().data());
	if(currentStaffID != 0) {
		removeStaff(currentStaffID, currentStaffName);
	} else {
		MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, zeroSelectionWarning);
	}
}

void StaffWindow::removeStaff(uint32 id, string name)	
{
	QString confirm =QString::fromLocal8Bit(removeStaffConfirm).arg(QString::fromLocal8Bit(name.c_str()));
	if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, smWindowTitle, confirm.toLocal8Bit().data())) return;
	uint32* staffid = new uint32(id);
	Message* action = new Message();
	action->setType(ACTION_REMOVESTAFF);
	action->setData(staffid);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::getAllStaff()
{
	ui.itemView->clearData();
	Message* action = new Message();
	action->setType(ACTION_GEALLSTAFF);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::addStaff(Staff* staff, QByteArray& data)
{
	if(staff->Name().empty()) {
		MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, emptyNameWarnning);
		return;
	}
	Message* action = new Message(ACTION_ADDSTAFF, staff);
	if(!data.isEmpty())
		action->setData2(&data);
	m_uiHandler->StartAction(*action);
	delete action;

}

void StaffWindow::modifyStaff(Staff* staff, QByteArray& data)
{
	if(staff->Name().empty()) {
		MessageBox::showMessageBox(this, QMessageBox::Warning, smWindowTitle, emptyNameWarnning);
		return;
	}
	Message* action = new Message(ACTION_MODIFYSTAFF, staff);
	if(!data.isEmpty())
		action->setData2(&data);
	m_uiHandler->StartAction(*action);
	delete action;

}

 void StaffWindow::browseMyInfo()
 {
 	Message* action = new Message();
	action->setType(ACTION_GETLOGGEDSTAFF);
	m_uiHandler->StartAction(*action);
	delete action;
}
 
void StaffWindow::changeMyPassword()
{
	PasswordWidget* passwordWindow = new PasswordWidget(this);
	connect(passwordWindow, SIGNAL(submitPassword(string, string)), this, SLOT(changePasswrod(string, string)));
	passwordWindow->show();
}

void StaffWindow::changePasswrod(string oldpw, string newpw)
{
	list<string>* pwList = new list<string>;
	pwList->push_back(oldpw);
	pwList->push_back(newpw);
	Message* action = new Message(ACTION_CHANGEPASSWORD, pwList);
	m_uiHandler->StartAction(*action);
	delete action;
}

 void StaffWindow::staffConfig()
 {
 	config = new StaffConfiguration(this);
	getJobType();
	getLevelType();
	getStatusType();
	connect(config->ui.pageJob, SIGNAL(submitted(list<Job>*)), this, SLOT(setJobs(list<Job>*)));
	connect(config->ui.pageLevel, SIGNAL(submitted(list<Level>*)), this, SLOT(setLevels(list<Level>*)));
	config->show();
 }

 void StaffWindow::setLevels(list<Level>* levels) 
 {
 	Message* action = new Message(ACTION_SETLEVELTYPE, levels);
	m_uiHandler->StartAction(*action);
	delete action;
 }

void StaffWindow::setJobs(list<Job>* jobs)
{
	 Message* action = new Message(ACTION_SETJOBTYPE, jobs);
	m_uiHandler->StartAction(*action);
	delete action;
}

void StaffWindow::showSmallIcon(bool flag)
{
	if(flag) {
		ui.mainToolBar->setIconSize(QSize(32, 32));
	} else {
		ui.mainToolBar->setIconSize(QSize(48, 48));
	}
}

void StaffWindow::showTextLabel(bool flag)
{
	if(flag) {
		ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	} else {
		ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	}
}

void StaffWindow::showToolBar(bool flag)
{
	if(flag) {
		ui.mainToolBar->show();
	} else {
		ui.mainToolBar->close();
	}
}
