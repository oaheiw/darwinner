#include "StaffDetail.h"
#include <QFont>
#include <string>
#include "common.h"
#include "Singleton.h"
#include <QString>
#include "Message.h"
#include "messagedef.h"
#include "DUIHandler.h"
#include "Job.h"
#include "Level.h"
#include "Status.h"
#include "Staff.h"
#include <QFileDialog>
#include <QFile>
#include "AppParameter.h"
#include "MessageBox.h"
#include "UiStrings.h"

StaffDetail::StaffDetail(QWidget *parent, int mode)
	: QWidget(parent)
{
	m_mode = mode;
	myinfo = false;
	setupUi();
	font = QFont("SimSun", 9);
	SettingFont(font);
	changeMode(m_mode);
//	connect(pushButtonModify, SIGNAL(clicked()), this, SLOT(modify()));
	connect(pushButtonPix, SIGNAL(clicked()), this, SLOT(selectPic()));
	connect(pushButtonSubmmit, SIGNAL(clicked()), this, SLOT(submit()));
}

StaffDetail::~StaffDetail()
{

}

 void StaffDetail::setupUi()
{
	noPic = QPixmap(":/staff/staff");//.scaled(180, 180,Qt::KeepAspectRatio ,Qt::SmoothTransformation);
	labelPortrait = new QLabel(this);
	labelPortrait->setPixmap(noPic);
	labelPortrait->setFixedSize(180, 240);
	labelPortrait->setFrameShape(QFrame::StyledPanel);
	labelPortrait->setFrameShadow(QFrame::Raised);
	labelPortrait->setAlignment(Qt::AlignCenter);

	lineEditId = new QLineEdit(this);
	lineEditName = new QLineEdit(this);
	lineEditName->setMaxLength(NAME_MAX_LEN);
	comboBoxSex = new QComboBox(this);
	comboBoxStatus = new QComboBox(this);
	comboBoxJob = new QComboBox(this);
	comboBoxLevel = new QComboBox(this);
	lineEditPhone = new QLineEdit(this);
	lineEditPhone->setMaxLength(PHONE_MAX_LEN);
	lineEditCell = new QLineEdit(this);
	lineEditCell->setMaxLength(PHONE_MAX_LEN);
	plainTextEditAddress = new QPlainTextEdit(this);
	plainTextEditAddress->setMinimumHeight(40);
	plainTextEditDescrption = new QPlainTextEdit(this);
	plainTextEditDescrption->setMinimumHeight(40);

	labelId = new QLabel(LOCAL8BITSTR(staffIDStr), this);
	labelName = new QLabel(LOCAL8BITSTR(staffNameStr), this);
	labelSex = new QLabel(LOCAL8BITSTR(staffSexStr), this);
	labelStatus = new QLabel(LOCAL8BITSTR(staffStatusStr), this);
	labelJob = new QLabel(LOCAL8BITSTR(staffJobStr), this);
	labelLevel = new QLabel(LOCAL8BITSTR(staffLevelStr), this);
	labelCell = new QLabel(LOCAL8BITSTR(staffCellStr), this);
	labelPhone = new QLabel(LOCAL8BITSTR(staffPhoneStr), this);
	labelDescrption = new QLabel(LOCAL8BITSTR(staffDescriptionStr), this);
	labelAddress = new QLabel(LOCAL8BITSTR(staffAddressStr), this);
	pushButtonPix = new QPushButton(LOCAL8BITSTR(choosePicStr), this);
	pushButtonModify = new QPushButton(LOCAL8BITSTR(editStr),  this);
	pushButtonSubmmit = new QPushButton(LOCAL8BITSTR(submitStr), this);
	pushButtonPix->setMinimumHeight(30);
	pushButtonModify->setMinimumHeight(30);
	pushButtonSubmmit->setMinimumHeight(30);
	pushButtonPix->setMaximumHeight(50);
	pushButtonModify->setMaximumHeight(50);
	pushButtonSubmmit->setMaximumHeight(50);
	pushButtonPix->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	pushButtonModify->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	pushButtonSubmmit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	comboBoxSex->addItem(LOCAL8BITSTR(sexUndefinedStr), SEX_UNDEFINE);
	comboBoxSex->addItem(LOCAL8BITSTR(sexMaleStr), SEX_MALE);
	comboBoxSex->addItem(LOCAL8BITSTR(sexFemaleStr), SEX_FEMALE);

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
 }
  
void StaffDetail::setJob(list<Job>* jobList)
{
	comboBoxJob->clear();
	list<Job>::iterator it = jobList->begin();
	while(jobList->end() != it)
	{
		comboBoxJob->addItem(LOCAL8BITSTR(it->name().c_str()), QVariant(it->id()));
		it++;
	}
}

void StaffDetail::setLevel(list<Level>* levelList)
{
	comboBoxLevel->clear();
	list<Level>::iterator it = levelList->begin();
	while(levelList->end() != it)
	{
		comboBoxLevel->addItem(LOCAL8BITSTR(it->name().c_str()), QVariant(it->id()));
		it++;
	}
}

void StaffDetail::setStatus(list<Status>* statusList)
{
	comboBoxStatus->clear();
	list<Status>::iterator it = statusList->begin();
	while(statusList->end() != it)
	{
	  comboBoxStatus->addItem(LOCAL8BITSTR(it->name().c_str()), QVariant(it->id()));
	  it++;
	}
}


  void StaffDetail::browseStaff(Staff* staff, bool flag)
  {
  	myinfo = flag;
	if(NULL != staff) {
		changeMode(SINFO_BROWSE);
		lineEditId->setText(QString::number(staff->id()));
		lineEditName->setText(LOCAL8BITSTR(staff->name().c_str()));
		comboBoxSex->setCurrentIndex(comboBoxSex->findData(staff->sex()));
		comboBoxStatus->setCurrentIndex(comboBoxStatus->findData(QVariant(staff->status())));
		comboBoxJob->setCurrentIndex(comboBoxJob->findData(QVariant(staff->type())));
		comboBoxLevel->setCurrentIndex(comboBoxLevel->findData(QVariant(staff->level())));
		lineEditPhone->setText(LOCAL8BITSTR(staff->phone().c_str()));
		lineEditCell->setText(LOCAL8BITSTR(staff->cell().c_str()));
		plainTextEditAddress->setPlainText(LOCAL8BITSTR(staff->address().c_str()));
		plainTextEditDescrption->setPlainText(LOCAL8BITSTR(staff->description().c_str()));
		userPicData.clear();
		labelPortrait->setPixmap(noPic);
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
			if(!myinfo) {
				comboBoxJob->setEnabled(true);
				comboBoxLevel->setEnabled(true);
				comboBoxSex->setEnabled(true);
				comboBoxStatus->setEnabled(true);
			}			
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
	if(lineEditId->text().isEmpty()) {
		MessageBox::showMessageBox(this, QMessageBox::Warning, smString, zeroSelectionWarning);
		return;
	}
	if(SINFO_NEW == m_mode) {		
		MessageBox::showMessageBox(this, QMessageBox::Warning, smString, smEditModeWarning);
		return;
	}
	changeMode(SINFO_MODIFY);
	if(NULL != staff) {
		lineEditId->setText(QString::number(staff->id()));
		lineEditName->setText(LOCAL8BITSTR(staff->name().c_str()));
		comboBoxSex->setCurrentIndex(staff->sex());
		comboBoxStatus->setCurrentIndex(staff->status());
		comboBoxJob->setCurrentIndex(staff->type());
		comboBoxLevel->setCurrentIndex(staff->level());
		lineEditPhone->setText(LOCAL8BITSTR(staff->phone().c_str()));
		lineEditCell->setText(LOCAL8BITSTR(staff->cell().c_str()));
		plainTextEditAddress->setPlainText(LOCAL8BITSTR(staff->address().c_str()));
		plainTextEditDescrption->setPlainText(LOCAL8BITSTR(staff->description().c_str()));
	}
}

 void StaffDetail::newStaff()
{
	if(SINFO_MODIFY == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, smString, abandonModifyWarning))
			return;
	}
	myinfo = false;
	Staff* staff = new Staff();
	staff->clear();
	userPicData.clear();
	lineEditId->setText(QString::number(staff->id()));
	lineEditName->setText(LOCAL8BITSTR(staff->name().c_str()));
	comboBoxSex->setCurrentIndex(staff->sex());
	comboBoxStatus->setCurrentIndex(staff->status());
	comboBoxJob->setCurrentIndex(staff->type());
	comboBoxLevel->setCurrentIndex(staff->level());
	lineEditPhone->setText(LOCAL8BITSTR(staff->phone().c_str()));
	lineEditCell->setText(LOCAL8BITSTR(staff->cell().c_str()));
	plainTextEditAddress->setPlainText(LOCAL8BITSTR(staff->address().c_str()));
	plainTextEditDescrption->setPlainText(LOCAL8BITSTR(staff->description().c_str()));
	labelPortrait->setPixmap(noPic);
	changeMode(SINFO_NEW);
	delete staff;
}

 void StaffDetail::modify()
 {
 	modifyStaff(NULL);
 }
 
void StaffDetail::selectPic()
{
	QString lastDir = LOCAL8BITSTR(Singleton<AppParameter>::instance()->getLastDir().c_str());
	QString fileName = QFileDialog::getOpenFileName(this, LOCAL8BITSTR(choosePicStr), 
								lastDir, LOCAL8BITSTR(imageFileStr));
	 if(!fileName.isEmpty()) {
		 std::string last = std::string(fileName.toLocal8Bit().data());
		 last = last.substr(0, last.find_last_of(DIR_SEPERATOR));
		 Singleton<AppParameter>::instance()->setLastDir(last);
		 QFile file(fileName);
		 file.open(QIODevice::ReadOnly);
		 if(file.size() > PIC_MAX_SIZE*MB) {
			 QString warning = LOCAL8BITSTR(imageSizeWarning).arg(PIC_MAX_SIZE);
			 MessageBox::showMessageBox(this, QMessageBox::Warning, smString, warning.toLocal8Bit().data());
			 return;
		 }
		 displayPic(file.readAll());
		 file.close();
	 }
}

void StaffDetail::displayPic(QByteArray& data)
{
	userPicData = data;
	if(!userPicData.isEmpty()) {
		QPixmap pic;
		pic.loadFromData(userPicData);
		if(pic.height() != 0) {
			if(pic.width()/pic.height() > labelPortrait->width()/labelPortrait->height())
				pic = pic.scaledToWidth(labelPortrait->width(), Qt::SmoothTransformation);
			else
				pic = pic.scaledToHeight(labelPortrait->height(), Qt::SmoothTransformation);
			labelPortrait->setPixmap(pic);
		} else {
			labelPortrait->setPixmap(noPic);
		}
	}
}

void StaffDetail::submit()
{
	Staff* staff = new Staff();
	staff->setaddress(string(plainTextEditAddress->toPlainText().toLocal8Bit().data()));
	staff->setcell(string(lineEditCell->text().toLocal8Bit().data()));
	staff->setdescription(string(plainTextEditDescrption->toPlainText().toLocal8Bit().data()));
	staff->setid(lineEditId->text().toUInt());
	staff->setlevel(comboBoxLevel->itemData(comboBoxLevel->currentIndex()).toUInt());
	staff->setname(string(lineEditName->text().toLocal8Bit().data()));
	staff->setpassword(emptyStr);
	staff->setphone(string(lineEditPhone->text().toLocal8Bit().data()));
	staff->setsex(comboBoxSex->itemData(comboBoxSex->currentIndex()).toUInt());
	staff->settype(comboBoxJob->itemData(comboBoxJob->currentIndex()).toUInt());
	staff->setstatus(comboBoxStatus->itemData(comboBoxStatus->currentIndex()).toUInt());

	if(SINFO_NEW == m_mode) {
		emit addedStaff(staff, userPicData);
	}
	else if(SINFO_MODIFY == m_mode) {
		emit modifiedStaff(staff, userPicData);
	}
}

