 #include <QtGui>
#include "Guide.h"
#include "Message.h"
#include "messagedef.h"
#include "DUIHandler.h"
#include "Staff.h"
#include "JobTypeWidget.h"
#include "Status.h"
#include "LevelWidget.h"
#include <list>
#include "ProgressWidget.h"
#include "UiStrings.h"
using namespace std;

 Guide::Guide(QWidget *parent)
     : QWizard(parent)
 {
	setWizardStyle(QWizard::ModernStyle);
	QFont font = QFont("SimSun", 9);
	setFont(font);
	level = new LevelWidget(this, 0);
	job = new JobTypeWidget(this, 0);
	m_message = NULL;
	progressBar = NULL;
	totalStep = 0;
	isfinished = false;
	addPage(new IntroPage);
	addPage(new SupperUserPage);
	addPage(new StaffInfoPage(level, job, this));
	addPage(new StaffRightsPage);
	addPage(new ConclusionPage);
	setButtonText(QWizard::BackButton, LOCAL8BITSTR("上一步"));
	setButtonText(QWizard::NextButton, LOCAL8BITSTR("下一步"));
	setButtonText(QWizard::CommitButton, LOCAL8BITSTR("确定"));
	setButtonText(QWizard::FinishButton, LOCAL8BITSTR("结束"));
	setButtonText(QWizard::CancelButton, LOCAL8BITSTR("取消"));
	setButtonText(QWizard::HelpButton, LOCAL8BITSTR("帮助"));

	setPixmap(QWizard::BannerPixmap, QPixmap(":/common/Resources/banner.png"));
	setPixmap(QWizard::LogoPixmap, QPixmap(":/common/Resources/cosmetic-text.png").scaled(100, 100,Qt::KeepAspectRatio ,Qt::SmoothTransformation));

	setWindowTitle(LOCAL8BITSTR("设置向导"));
 }

 void Guide::OnEvent(Message& ev)
 {
	 switch(ev.type()) {
		case EVENT_WIZARD: 
		{
			show();
			break;
		}
		case EVENT_INIT:
		case EVENT_SETSUPERUSER:
		case EVENT_SETJOBTYPE:
		case EVENT_SETLEVELTYPE:
		{
			progressBar->setValue(++totalStep);
			break;
		}
		case EVENT_INIT_FINISHED:
		{
			progressBar->setValue(++totalStep);
			initData();
			break;
		}
		case EVENT_SETSTATUSTYPE://wait for this to indicate guide finished
		{
			progressBar->setValue(++totalStep);
			progressBar->close();
			if(!isfinished) {
				isfinished = true;
				m_message = new Message(ACTION_SYSTEM_START);
				m_uiHandler->StartAction(*m_message);
				delete m_message;
			}
			break;
		}
		case EVENT_SYSTEM_START:
		{
			 QDialog::accept();
			 break;
		}
	 }
 }

void Guide::accept()
{
	button(QWizard::BackButton)->setDisabled(true);
	button(QWizard::FinishButton)->setDisabled(true);
	button(QWizard::CancelButton)->setDisabled(true);
	progressBar = new ProgressWidget(LOCAL8BITSTR("正在初始化数据库，请稍候……"), 0, 6, this);
	progressBar->show();
	totalStep = 0;
	initDb();
 }

 void Guide::initDb()
 {
	m_message = new Message(ACTION_INIT_DB);
	m_uiHandler->StartAction(*m_message);
	delete m_message;
 }

 void Guide::initData()
 {
 //*********************init super staff*************************//
	Staff* staff = new Staff();
	staff->SetPassword(field("password").toString().toLocal8Bit().data());	
	m_message = new Message(ACTION_SETSUPERUSER, staff);
	m_uiHandler->StartAction(*m_message);
	delete m_message;

//*********************init staff job*************************//
	list<Job>* jobList = job->getJobList();
//	if(jobList->empty())
	{
		Job temp;
		temp.setName("未设定");
		temp.setDescription("系统默认职务");
		jobList->push_front(temp);
	}
	m_message = new Message(ACTION_SETJOBTYPE, (void*)jobList);
	m_uiHandler->StartAction(*m_message);
	delete m_message;

//*********************init staff level*************************//
	list<Level>* levelList = level->getLevelList();
//	if(levelList->empty())
	{
		Level temp;
		temp.setName("未设定");
		temp.setDescription("系统默认等级");
		levelList->push_front(temp);
	}
	m_message = new Message(ACTION_SETLEVELTYPE, (void*)levelList);
	m_uiHandler->StartAction(*m_message);
	delete m_message;

//*********************init staff status*************************//
	list<Status>* statusList = new list<Status>;
	Status temp;
	temp.setName("在职");
	statusList->push_back(temp);
	temp.setName("休假");
	statusList->push_back(temp);
	temp.setName("空闲");
	statusList->push_back(temp);
	temp.setName("忙碌");
	statusList->push_back(temp);
	temp.setName("离职");
	statusList->push_back(temp);

	m_message = new Message(ACTION_SETSTATUSTYPE, (void*)statusList);
	m_uiHandler->StartAction(*m_message);
	delete m_message;
 }



 IntroPage::IntroPage(QWidget *parent)
     : QWizardPage(parent)
 {
	 setTitle(LOCAL8BITSTR("设置向导"));
	 	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/common/Resources/watermark.png"));


	 label = new QLabel(LOCAL8BITSTR("这是您第一次运行Cosmetic（科思美）美容美发业运营系统。本向导将会引导您完成系统运行所必须的基础设置。除了“超级用户”相关的内容，其它设置尽可以在日后再次修改。"));
     label->setWordWrap(true);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(label);
     setLayout(layout);
 }

 SupperUserPage::SupperUserPage(QWidget *parent)
     : QWizardPage(parent)
 {
	setTitle(LOCAL8BITSTR("超级用户"));
	setSubTitle(LOCAL8BITSTR("超级用户在本系统中具有最高权限，它是您第一次登录系统以及进行各种高级设置所能使用的唯一帐号。其工号为<font color=\"#ff0000\"; size=+1><b>10000</b></font>，请为其设置密码，并牢记其信息！"));

	passwordLabel = new QLabel(LOCAL8BITSTR("新密码"));
	passwordLineEdit = new QLineEdit;
	passwordLineEdit->setEchoMode(QLineEdit::Password);
	passwordLineEdit->setMaximumWidth(200);
	passwordLineEdit->setMaxLength(PW_MAX_LEN);
	passwordLabel->setBuddy(passwordLineEdit);

	confirmLabel = new QLabel(LOCAL8BITSTR("确认密码"));
	confirmLineEdit = new QLineEdit;
	confirmLineEdit->setEchoMode(QLineEdit::Password);
	confirmLineEdit->setMaxLength(PW_MAX_LEN);
	confirmLineEdit->setMaximumWidth(200);
	confirmLabel->setBuddy(confirmLineEdit);

	registerField("password*", passwordLineEdit);
	registerField("confirm*", confirmLineEdit);


	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(passwordLabel, 0, 0);
	layout->addWidget(passwordLineEdit, 0, 1);
	layout->addWidget(confirmLabel, 1, 0);
	layout->addWidget(confirmLineEdit, 1, 1);
	layout->setContentsMargins(0, 20, 200, 30);
	setLayout(layout);
 }

 bool SupperUserPage::isComplete() const{
	 return !field("password").toString().isEmpty() && field("password").toString() == field("confirm").toString();
 }

//****************************StaffInfoPage************************//
 StaffInfoPage::StaffInfoPage(LevelWidget* levelWidget, JobTypeWidget* joblWidget, QWidget *parent)
     : QWizardPage(parent)
 {
	setTitle(LOCAL8BITSTR("职务及级别"));
	setSubTitle(LOCAL8BITSTR("请录入贵公司的员工职务和级别，及其余相关信息。系统已经预置了一些项目，您可以继续添加、修改、删除。在本系统中，员工薪水是按照公式：<center><font color=\"#336699\"><b>职务工资+级别工资+业绩×(职务提成+级别提成)</b></font></center>来计算的。"));

	level = levelWidget;
	job = joblWidget;

	jobLabel = new QLabel(LOCAL8BITSTR("职务设置："));
	levelLabel = new QLabel(LOCAL8BITSTR("级别设置："));
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(jobLabel, 0, 0, 1, 1);
	layout->addWidget(levelLabel, 0, 1, 1, 1);
	layout->addWidget(job, 1, 0, 1, 1);
	layout->addWidget(level, 1, 1, 1, 1);
	layout->setMargin(0);
	setLayout(layout);
	}

 void StaffInfoPage::initializePage()
 {
	 {
	 list<Job> jobList;
	 Job temp;
	 temp.setName("老板");
	 jobList.push_back(temp);
	 temp.setName("店长");
	 jobList.push_back(temp);
	 temp.setName("收银员");
	 jobList.push_back(temp);
	 temp.setName("美发师");
	 jobList.push_back(temp);
	 temp.setName("美发助理");
	 jobList.push_back(temp);
	 temp.setName("美容师");
	 jobList.push_back(temp);
	 temp.setName("美容助理");
	 jobList.push_back(temp);
	 temp.setName("按摩师");
	 jobList.push_back(temp);
	 temp.setName("按摩助理");
	 jobList.push_back(temp);

	 job->pushjobs(&jobList);
	 }

	{
	list<Level> levelList;
	Level temp;
	temp.setName("临时员工");
	levelList.push_back(temp);
	temp.setName("试用员工");
	levelList.push_back(temp);
	temp.setName("普通员工");
	levelList.push_back(temp);
	temp.setName("经验员工");
	levelList.push_back(temp);
	temp.setName("资深员工");
	levelList.push_back(temp);
	
	level->pushLevels(&levelList);
	}

 }

 StaffRightsPage::StaffRightsPage(QWidget *parent)
     : QWizardPage(parent)
 {
	 setTitle(LOCAL8BITSTR("职务权限"));
     setSubTitle(LOCAL8BITSTR("请为不同职务的员工设置其在本系统中的权限。请谨慎选择，以免造成不必要的信息泄露。"));

/*
     outputDirLabel = new QLabel(tr("&Output directory:"));
     outputDirLineEdit = new QLineEdit;
     outputDirLabel->setBuddy(outputDirLineEdit);

     headerLabel = new QLabel(tr("&Header file name:"));
     headerLineEdit = new QLineEdit;
     headerLabel->setBuddy(headerLineEdit);

     implementationLabel = new QLabel(tr("&Implementation file name:"));
     implementationLineEdit = new QLineEdit;
     implementationLabel->setBuddy(implementationLineEdit);

     registerField("outputDir*", outputDirLineEdit);
     registerField("header*", headerLineEdit);
     registerField("implementation*", implementationLineEdit);

     QGridLayout *layout = new QGridLayout;
     layout->addWidget(outputDirLabel, 0, 0);
     layout->addWidget(outputDirLineEdit, 0, 1);
     layout->addWidget(headerLabel, 1, 0);
     layout->addWidget(headerLineEdit, 1, 1);
     layout->addWidget(implementationLabel, 2, 0);
     layout->addWidget(implementationLineEdit, 2, 1);
     setLayout(layout);
	 */
 }

 void StaffRightsPage::initializePage()
 {
	 /*
     QString className = field("className").toString();
     headerLineEdit->setText(className.toLower() + ".h");
     implementationLineEdit->setText(className.toLower() + ".cpp");
     outputDirLineEdit->setText(QDir::convertSeparators(QDir::tempPath()));
	 */
 }

 ConclusionPage::ConclusionPage(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(LOCAL8BITSTR("设置完成"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/common/Resources/watermark.png"));

     label = new QLabel;
     label->setWordWrap(true);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(label);
     setLayout(layout);

 }

 void ConclusionPage::initializePage()
 {
     QString finishText = wizard()->buttonText(QWizard::FinishButton);
     finishText.remove('&');
	 label->setText(LOCAL8BITSTR("请点击“%1”键以完成向导，进入登录界面。")
                    .arg(finishText));
 }
