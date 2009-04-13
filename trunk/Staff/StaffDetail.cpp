#include "StaffDetail.h"
#include <QFont>
#include "Staff.h"

StaffDetail::StaffDetail(QWidget *parent, int mode, Staff* staff)
	: QFrame(parent)
{
	m_mode = mode;
	m_staff = staff;
	setupUi();
	QFont font = QFont("SimSun", 9);
	SettingFont(font);
}

StaffDetail::~StaffDetail()
{

}

 void StaffDetail::setupUi()
{
//	QStyle* style = new QStyle();
//	setStyle(style);
	this->setFrameShape(QFrame::StyledPanel);
	this->setFrameShadow(QFrame::Raised);
    labelPortrait = new QLabel(QString::fromLocal8Bit("没有照片"),this);
	labelPortrait->setFixedSize(180, 240);
    labelPortrait->setFrameShape(QFrame::Box);
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
    plainTextEditDescrption = new QPlainTextEdit(this);
    

    labelId = new QLabel(QString::fromLocal8Bit("工号"), this);
    labelName = new QLabel(QString::fromLocal8Bit("姓名"), this);
    labelSex = new QLabel(QString::fromLocal8Bit("性别"), this);
    labelStatus = new QLabel(QString::fromLocal8Bit("状态"), this);
	labelJob = new QLabel(QString::fromLocal8Bit("职务"), this);
    labelLevel = new QLabel(QString::fromLocal8Bit("等级"), this);
    labelCell = new QLabel(QString::fromLocal8Bit("手机"), this);
    labelPhone = new QLabel(QString::fromLocal8Bit("固话"), this);
    labelDescrption = new QLabel(QString::fromLocal8Bit("自述"), this);
    labelAddress = new QLabel(QString::fromLocal8Bit("地址"), this);
	pushButtonPix = new QPushButton(QString::fromLocal8Bit("选择照片"), this);
	pushButtonModify = new QPushButton(QString::fromLocal8Bit("修改信息"),  this);
	pushButtonSubmmit = new QPushButton(QString::fromLocal8Bit("提交更改"), this);
   
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

	QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->addWidget(pushButtonModify);
	horizontalLayout->addWidget(pushButtonPix);
	horizontalLayout->addWidget(pushButtonSubmmit);
	
	layout->addLayout(horizontalLayout, 10, 0, 1, 8);
	layout->setRowStretch(10, 10);
	layout->setRowStretch(9, 1);
	layout->setRowStretch(8, 1);
	
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

  void StaffDetail::pushStaff(Staff* staff, int mode)
  {
	  m_staff = staff;
	  lineEditId->setText(QString::number(m_staff->ID()));
	  lineEditName->setText(QString::fromLocal8Bit(m_staff->Name().c_str()));
	  comboBoxSex->setCurrentIndex(m_staff->Sex());
    comboBoxStatus->setCurrentIndex(0);
	comboBoxJob->setCurrentIndex(m_staff->Type());
    comboBoxLevel->setCurrentIndex(m_staff->Level());
	lineEditPhone->setText(QString::fromLocal8Bit(m_staff->phone().c_str()));
	lineEditCell->setText(QString::fromLocal8Bit(m_staff->cell().c_str()));
	plainTextEditAddress->setPlainText(QString::fromLocal8Bit(m_staff->address().c_str()));
    plainTextEditDescrption->setPlainText(QString::fromLocal8Bit(m_staff->Descrp().c_str()));
  }