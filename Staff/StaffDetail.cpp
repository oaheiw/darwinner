#include "StaffDetail.h"
#include <QFont>
#include "common.h"
#include <QString>
#include "Message.h"
#include "messagedef.h"
#include "DUIHandler.h"
#include "Job.h"
#include "Level.h"
#include "Status.h"
#include "Staff.h"

StaffDetail::StaffDetail(QWidget *parent, int mode)
	: QWidget(parent)
{
	m_mode = mode;
	setupUi();
	font = QFont("SimSun", 9);
	SettingFont(font);
	changeMode(mode);
	connect(pushButtonModify, SIGNAL(clicked()), this, SLOT(modify()));
	connect(pushButtonPix, SIGNAL(clicked()), this, SLOT(selectPic()));
	connect(pushButtonSubmmit, SIGNAL(clicked()), this, SLOT(submit()));
}

StaffDetail::~StaffDetail()
{

}

 void StaffDetail::setupUi()
{
	labelPortrait = new QLabel(QString::fromLocal8Bit("没有照片"),this);
	labelPortrait->setFixedSize(180, 240);
	labelPortrait->setFrameShape(QFrame::StyledPanel);
	labelPortrait->setFrameShadow(QFrame::Raised);
	labelPortrait->setAlignment(Qt::AlignCenter);

	lineEditId = new QLineEdit(this);
	lineEditName = new QLineEdit(this);
	comboBoxSex = new QComboBox(this);
	comboBoxStatus = new QComboBox(this);
	comboBoxJob = new QComboBox(this);
	comboBoxLevel = new QComboBox(this);
	lineEditPhone = new QLineEdit(this);
	lineEditCell = new QLineEdit(this);
	plainTextEditAddress = new QPlainTextEdit(this);
//	plainTextEditAddress->setMaximumHeight(60);
	plainTextEditAddress->setMinimumHeight(40);
	plainTextEditDescrption = new QPlainTextEdit(this);
//	plainTextEditDescrption->setMaximumHeight(60);
	plainTextEditDescrption->setMinimumHeight(40);

	labelId = new QLabel(QString::fromLocal8Bit("工号"), this);
	labelName = new QLabel(QString::fromLocal8Bit("姓名"), this);
	labelSex = new QLabel(QString::fromLocal8Bit("性别"), this);
	labelStatus = new QLabel(QString::fromLocal8Bit("状态"), this);
	labelJob = new QLabel(QString::fromLocal8Bit("职务"), this);
	labelLevel = new QLabel(QString::fromLocal8Bit("等级"), this);
	labelCell = new QLabel(QString::fromLocal8Bit("手机"), this);
	labelPhone = new QLabel(QString::fromLocal8Bit("固话"), this);
	labelDescrption = new QLabel(QString::fromLocal8Bit("备注"), this);
	labelAddress = new QLabel(QString::fromLocal8Bit("地址"), this);
	pushButtonPix = new QPushButton(QString::fromLocal8Bit("选择照片(&P)"), this);
	pushButtonModify = new QPushButton(QString::fromLocal8Bit("修改(&G)"),  this);
	pushButtonSubmmit = new QPushButton(QString::fromLocal8Bit("提交(&Q)"), this);
	pushButtonPix->setMinimumHeight(30);
	pushButtonModify->setMinimumHeight(30);
	pushButtonSubmmit->setMinimumHeight(30);
	pushButtonPix->setMaximumHeight(50);
	pushButtonModify->setMaximumHeight(50);
	pushButtonSubmmit->setMaximumHeight(50);
	pushButtonPix->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	pushButtonModify->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	pushButtonSubmmit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//	comboBoxJob->addItem(QString::fromLocal8Bit("未设置"), 0);
//	comboBoxJob->setCurrentIndex(1);
//	comboBoxLevel->addItem(QString::fromLocal8Bit("未设置"), 0);
//	comboBoxLevel->setCurrentIndex(1);
//	comboBoxStatus->setCurrentIndex(1);
	comboBoxSex->addItem(QString::fromLocal8Bit("未设定"), 0);
	comboBoxSex->addItem(QString::fromLocal8Bit("男"), 1);
	comboBoxSex->addItem(QString::fromLocal8Bit("女"), 2);
//	comboBoxSex->setCurrentIndex(0);


	labelId->setBuddy(lineEditId);
	labelName->setBuddy(lineEditName);
	labelJob->setBuddy(comboBoxJob);
	labelLevel->setBuddy(comboBoxLevel);
	labelSex->setBuddy(comboBoxSex);
	labelStatus->setBuddy(comboBoxStatus);
	labelPhone->setBuddy(lineEditPhone);
	labelCell->setBuddy(lineEditCell);
	labelDescrption->setBuddy(plainTextEditDescrption);
	labelAddress->setBuddy(plainTextEditAddress);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(labelId, 0, 0, 1, 1);
	layout->addWidget(lineEditId, 0, 1, 1, 1);


	layout->addWidget(labelName, 1, 0, 1, 1);
	layout->addWidget(lineEditName, 1, 1, 1, 1);
	layout->addWidget(labelSex, 2, 0, 1, 1);
	layout->addWidget(comboBoxSex, 2, 1, 1, 1);
	layout->addWidget(labelStatus, 3, 0, 1, 1);
	layout->addWidget(comboBoxStatus, 3, 1, 1, 1);
	layout->addWidget(labelJob, 4, 0, 1, 1);
	layout->addWidget(comboBoxJob, 4, 1, 1, 1);
	layout->addWidget(labelLevel, 5, 0, 1, 1);
	layout->addWidget(comboBoxLevel, 5, 1, 1, 1);
	layout->addWidget(labelPhone, 6, 0, 1, 1);
	layout->addWidget(lineEditPhone, 6, 1, 1, 1);
	layout->addWidget(labelCell, 7, 0, 1, 1);
	layout->addWidget(lineEditCell, 7, 1, 1, 1);
	layout->addWidget(labelPortrait, 0, 2, 8, 6);
	layout->addWidget(labelAddress, 8, 0, 1, 1);
	layout->addWidget(plainTextEditAddress, 8, 1, 1, 7);
	layout->addWidget(labelDescrption, 9, 0, 1, 1);
	layout->addWidget(plainTextEditDescrption, 9, 1, 1, 7);

	QHBoxLayout* horizontalLayout = new QHBoxLayout();
	horizontalLayout->addWidget(pushButtonModify);
	horizontalLayout->addWidget(pushButtonPix);
	horizontalLayout->addWidget(pushButtonSubmmit);

	layout->addLayout(horizontalLayout, 10, 0, 2, 8);
	layout->setRowStretch(10, 2);
	layout->setRowStretch(9, 1);
	layout->setRowStretch(8, 1);
	layout->setMargin(0);
	setLayout(layout);
  }

  void StaffDetail::SettingFont(QFont& font)
 {
	font.setBold(true);
	labelPortrait->setFont(font);
	font.setBold(false);
	lineEditId->setFont(font);
	lineEditName->setFont(font);
	labelId->setFont(font);
	labelName->setFont(font);
	labelJob->setFont(font);
	comboBoxJob->setFont(font);
	comboBoxLevel->setFont(font);
	labelLevel->setFont(font);
	labelSex->setFont(font);
	comboBoxSex->setFont(font);
	comboBoxStatus->setFont(font);
	labelStatus->setFont(font);
	lineEditCell->setFont(font);
	labelPhone->setFont(font);
	lineEditPhone->setFont(font);
	labelCell->setFont(font);
	labelDescrption->setFont(font);
	labelAddress->setFont(font);
	plainTextEditAddress->setFont(font);
	plainTextEditDescrption->setFont(font);
	pushButtonPix->setFont(font);
	pushButtonModify->setFont(font);
	pushButtonSubmmit->setFont(font);
	QToolTip::setFont(font);
 }
  
void StaffDetail::setJob(list<Job>* jobList)
{
	list<Job>::iterator it = jobList->begin();
	while(jobList->end() != it)
	{
		comboBoxJob->addItem(QString::fromLocal8Bit(it->name().c_str()), QVariant::fromValue(it->id()));
		it++;
	}
}

void StaffDetail::setLevel(list<Level>* levelList)
{
	
	list<Level>::iterator it = levelList->begin();
	while(levelList->end() != it)
	{
		comboBoxLevel->addItem(QString::fromLocal8Bit(it->name().c_str()), QVariant::fromValue(it->id()));
		it++;
	}
}

  void StaffDetail::setStatus(list<Status>* statusList)
  {
	  
	  list<Status>::iterator it = statusList->begin();
	  while(statusList->end() != it)
	  {
		  comboBoxStatus->addItem(QString::fromLocal8Bit(it->name().c_str()), QVariant::fromValue(it->id()));
		  it++;
	  }
  }


  void StaffDetail::browseStaff(Staff* staff)
  {
	if(NULL != staff) {
		changeMode(SINFO_BROWSE);
		lineEditId->setText(QString::number(staff->ID()));
		lineEditName->setText(QString::fromLocal8Bit(staff->Name().c_str()));
		comboBoxSex->setCurrentIndex(comboBoxSex->findData(staff->Sex()));
		comboBoxStatus->setCurrentIndex(comboBoxStatus->findData(QVariant::fromValue(staff->status())));
		comboBoxJob->setCurrentIndex(comboBoxJob->findData(QVariant::fromValue(staff->Type())));
		comboBoxLevel->setCurrentIndex(comboBoxLevel->findData(QVariant::fromValue(staff->Level())));
		lineEditPhone->setText(QString::fromLocal8Bit(staff->phone().c_str()));
		lineEditCell->setText(QString::fromLocal8Bit(staff->cell().c_str()));
		plainTextEditAddress->setPlainText(QString::fromLocal8Bit(staff->address().c_str()));
		plainTextEditDescrption->setPlainText(QString::fromLocal8Bit(staff->Descrp().c_str()));
	}
  }

 void StaffDetail::changeMode(int mode)
{
	m_mode = mode;
	switch(mode) {
		case SINFO_BROWSE:
		{		 
			lineEditId->setReadOnly(true);
			lineEditName->setReadOnly(true);
			comboBoxJob->setEnabled(false);
			comboBoxLevel->setEnabled(false);
			comboBoxSex->setEnabled(false);
			comboBoxStatus->setEnabled(false);
			lineEditCell->setReadOnly(true);
			lineEditPhone->setReadOnly(true);
			plainTextEditAddress->setReadOnly(true);
			plainTextEditDescrption->setReadOnly(true);
			pushButtonPix->setEnabled(false);
			pushButtonModify->setEnabled(true);
			pushButtonSubmmit->setEnabled(false);
			break;
		}
		case SINFO_MODIFY:
		case SINFO_NEW:
		{
			lineEditId->setReadOnly(true);
			lineEditName->setReadOnly(false);
			comboBoxJob->setEnabled(true);
			comboBoxLevel->setEnabled(true);
			comboBoxSex->setEnabled(true);
			comboBoxStatus->setEnabled(true);
			lineEditCell->setReadOnly(false);
			lineEditPhone->setReadOnly(false);
			plainTextEditAddress->setReadOnly(false);
			plainTextEditDescrption->setReadOnly(false);
			pushButtonPix->setEnabled(true);
			pushButtonModify->setEnabled(false);
			pushButtonSubmmit->setEnabled(true);
			break;
		}
	}
}

 void StaffDetail::modifyStaff(Staff* staff)
{
		changeMode(SINFO_MODIFY);
	if(NULL != staff) {
		lineEditId->setText(QString::number(staff->ID()));
		lineEditName->setText(QString::fromLocal8Bit(staff->Name().c_str()));
		comboBoxSex->setCurrentIndex(staff->Sex());
		comboBoxStatus->setCurrentIndex(staff->status());
		comboBoxJob->setCurrentIndex(staff->Type());
		comboBoxLevel->setCurrentIndex(staff->Level());
		lineEditPhone->setText(QString::fromLocal8Bit(staff->phone().c_str()));
		lineEditCell->setText(QString::fromLocal8Bit(staff->cell().c_str()));
		plainTextEditAddress->setPlainText(QString::fromLocal8Bit(staff->address().c_str()));
		plainTextEditDescrption->setPlainText(QString::fromLocal8Bit(staff->Descrp().c_str()));
	}
}

 void StaffDetail::newStaff()
{
	Staff* staff = new Staff();
	staff->clear();
	lineEditId->setText(QString::number(staff->ID()));
	lineEditName->setText(QString::fromLocal8Bit(staff->Name().c_str()));
	comboBoxSex->setCurrentIndex(staff->Sex());
	comboBoxStatus->setCurrentIndex(staff->status());
	comboBoxJob->setCurrentIndex(staff->Type());
	comboBoxLevel->setCurrentIndex(staff->Level());
	lineEditPhone->setText(QString::fromLocal8Bit(staff->phone().c_str()));
	lineEditCell->setText(QString::fromLocal8Bit(staff->cell().c_str()));
	plainTextEditAddress->setPlainText(QString::fromLocal8Bit(staff->address().c_str()));
	plainTextEditDescrption->setPlainText(QString::fromLocal8Bit(staff->Descrp().c_str()));
	changeMode(SINFO_NEW);
	delete staff;
}

 void StaffDetail::modify()
 {
 	modifyStaff(NULL);
 }
 
void StaffDetail::selectPic()
{
	
}

void StaffDetail::submit()
{
	if(lineEditName->text().isEmpty()) {
//		QToolTip::showText(lineEditName->pos(), QString::fromLocal8Bit("姓名不能为空"), pushButtonSubmmit, QRect(0, 0 , 200,200));
//		lineEditName->setToolTip(QString::fromLocal8Bit("姓名不能为空"));
//		return;
	}
	Staff* staff = new Staff();
	staff->SetAddress(plainTextEditAddress->toPlainText().toLocal8Bit().data());
	staff->SetCell(lineEditCell->text().toLocal8Bit().data());
	staff->SetDescrp(plainTextEditDescrption->toPlainText().toLocal8Bit().data());
	staff->SetID(lineEditId->text().toUInt());
	staff->SetLevel(comboBoxLevel->itemData(comboBoxLevel->currentIndex()).toUInt());
	staff->SetName(lineEditName->text().toLocal8Bit().data());
	staff->SetPassword("");
	staff->SetPhone(lineEditPhone->text().toLocal8Bit().data());
	staff->SetSex(comboBoxSex->itemData(comboBoxSex->currentIndex()).toUInt());
	staff->SetType(comboBoxJob->itemData(comboBoxJob->currentIndex()).toUInt());
	staff->SetStatus(comboBoxStatus->itemData(comboBoxStatus->currentIndex()).toUInt());

	if(SINFO_NEW == m_mode) {
		emit addedStaff(staff);
	}
	else if(SINFO_MODIFY == m_mode) {
		emit modifiedStaff(staff);
	}
}
