#include "SSLoginWindow.h"
#include <string>
#include "messagedef.h"
#include "Staff.h"
#include "Message.h"
#include "DUIHandler.h"
//#include <QString>
//#include <QLabel>

SSLoginWindow::SSLoginWindow(QWidget *parent, DUIHandler* handler)
	: QDialog(parent)
{
	setupUi();
	QFont font = QFont("SimSun", 9);
	SettingFont(font);
	m_uiHandler = handler;
}

SSLoginWindow::~SSLoginWindow()
{

}

void SSLoginWindow::OnEvent(Message& ev) 
{
	switch(ev.type()) {
		case EVENT_LOGGEDIN:
		{
			hide();
			break;
		}
		case EVENT_SYSTEM_START:
		case EVENT_LOGGEDOFF:
		{
			show();
			break;
		}
		case EVENT_EXIT:
		{
			close();
			break;
		}
		default:
		{
			hide();
			break;
		}
	}
}

void SSLoginWindow::Login()
{
	Staff* stu = new Staff();
	stu->SetID(idLineEdit->text().toUInt());
	stu->SetPassword(pwLineEdit->text().toStdString());
	Message* action = new Message(stu);
	action->setType(ACTION_LOGIN);
	m_uiHandler->StartAction(*action);
	delete action;
}

void SSLoginWindow::setupUi()
{
	const QIcon icon = QIcon(QString::fromUtf8(":/icons/Resources/Cosmetic.png"));
	logoLabel = new QLabel(this);
//	logoLabel->setGeometry(QRect(0, 0, 128, 128));
	logoLabel->setPixmap(QPixmap(":/icons/Resources/cosmetic-text.png").scaled(100, 100,Qt::KeepAspectRatio ,Qt::SmoothTransformation));
//	setTitle(QString::fromLocal8Bit("<i>Cosmetic（科思美）美容美发业运营系统</i>&trade;"));
//	setSubTitle(QString::fromLocal8Bit("请录入您的用户名和密码，以登录系统。"));
	setWindowTitle(QString::fromLocal8Bit("Cosmetic（科思美）美容美发业运营系统"));

	loginGroupBox = new QGroupBox(QString::fromLocal8Bit("员工入口"), this);

	idLabel = new QLabel(QString::fromLocal8Bit("用户名(&N)"), loginGroupBox);
	idLineEdit = new QLineEdit(loginGroupBox);
	idLabel->setBuddy(idLineEdit);
	idLineEdit->setValidator(new QIntValidator(idLineEdit));

	pwLabel = new QLabel(QString::fromLocal8Bit("密码(&P)"), loginGroupBox);
	pwLineEdit = new QLineEdit(loginGroupBox);
	pwLineEdit->setEchoMode(QLineEdit::Password);
	pwLabel->setBuddy(pwLineEdit);

	pushButtonLogin = new QPushButton(this);
	pushButtonLogin->setText(QString::fromLocal8Bit("登录(&L)"));
	pushButtonExit = new QPushButton(this);
	pushButtonExit->setText(QString::fromLocal8Bit("退出(&X)"));


//	buttonLayout->setAlignment(pushButtonLogin, Qt::AlignCenter);
//	buttonLayout->setAlignment(pushButtonExit, Qt::AlignCenter);
	
	QGridLayout *loginLayout = new QGridLayout(loginGroupBox);
	loginLayout->addWidget(idLabel, 0, 0, 1, 1);
	loginLayout->addWidget(idLineEdit, 0, 1, 1, 3);
	loginLayout->addWidget(pwLabel, 1, 0, 1, 1);
	loginLayout->addWidget(pwLineEdit, 1, 1, 1, 3);
	loginLayout->addWidget(pushButtonLogin, 3, 1, Qt::AlignCenter);
	loginLayout->addWidget(pushButtonExit, 3, 3, Qt::AlignCenter);
	loginGroupBox->setLayout(loginLayout);

	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(logoLabel);
	mainLayout->addWidget(loginGroupBox);
	setLayout(mainLayout);

	setFixedSize(380, 128);

	connect(pushButtonExit, SIGNAL(clicked()), this, SLOT(close()));
	connect(pushButtonLogin, SIGNAL(clicked()), this, SLOT(Login()));
}

void SSLoginWindow::SettingFont(QFont& font)
 {
	 font.setBold(true);
	 loginGroupBox->setFont(font);

	 font.setBold(false);
	 pushButtonLogin->setFont(font);
	 pushButtonExit->setFont(font);
	 idLabel->setFont(font);
	 pwLabel->setFont(font);
	 pwLineEdit->setFont(font);
	 idLineEdit->setFont(font);
 }