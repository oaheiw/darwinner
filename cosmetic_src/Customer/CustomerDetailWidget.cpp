#include "CustomerDetailWidget.h"
#include "Singleton.h"
#include "AppParameter.h"
#include <QFileDialog>
#include <QFile>
#include "MessageBox.h"
#include "UiStrings.h"
#include "Customer.h"
#include "CustomerLevel.h"
#include <QByteArray>
#include <QStandardItemModel>

CustomerDetailWidget::CustomerDetailWidget(QWidget *parent, uint32 mode)
: QWidget(parent),m_mode(mode)
{
	m_customerPicData.clear();
	m_dataModel = new QStandardItemModel(0, 0, this);
	ui.setupUi(this);

	ui.cardsTreeView->setModel(m_dataModel);
	ui.sexComboBox->addItem(LOCAL8BITSTR(sexUndefinedStr), SEX_UNDEFINE);
	ui.sexComboBox->addItem(LOCAL8BITSTR(sexMaleStr), SEX_MALE);
	ui.sexComboBox->addItem(LOCAL8BITSTR(sexFemaleStr), SEX_FEMALE);

	changeMode(m_mode);
	connect(ui.picButton, SIGNAL(clicked()), this, SLOT(selectPicture()));
	connect(ui.submitButton, SIGNAL(clicked()), this, SLOT(submit()));
	m_zeroPicture = QPixmap(":/customer/customer").
		scaled(ui.imageLabel->width(), ui.imageLabel->height(), 
		Qt::KeepAspectRatio ,Qt::SmoothTransformation);
	displayPicture(m_customerPicData);
}

CustomerDetailWidget::~CustomerDetailWidget()
{

}



void CustomerDetailWidget::browseCustomer(Customer* data){
	if(CUSTOMER_NEW == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox
			(this, QMessageBox::Question, cmString, cmCustomerEditModeWarning))
			return;
	}
	if(CUSTOMER_MODIFY == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox
			(this, QMessageBox::Question, cmString, abandonModifyWarning))
			return;
	}
	changeMode(CUSTOMER_BROWSE);
	ui.addressPlainTextEdit->setPlainText(LOCAL8BITSTR(data->address().c_str()));
	//ui.cardslistView
	ui.cellLineEdit->setText(LOCAL8BITSTR(data->cell().c_str()));
	ui.consumeLcdNumber->display(QString::number(data->getTotalConsume()));
	ui.depositLcdNumber->display(QString::number(data->getDeposit()));
	ui.descPlainTextEdit->setPlainText(LOCAL8BITSTR(data->description().c_str()));
	ui.idLcdNumber->display(QString::number(data->id()));
	ui.levelComboBox->setCurrentIndex(ui.levelComboBox->findData(data->getLevel()));
	ui.nameLineEdit->setText(LOCAL8BITSTR(data->name().c_str()));
	ui.phoneLineEdit->setText(LOCAL8BITSTR(data->phone().c_str()));
	ui.sexComboBox->setCurrentIndex(ui.sexComboBox->findData(data->sex()));
	ui.timesLcdNumber->display(QString::number(data->getConsumeTime()));
}

void CustomerDetailWidget::clearData() {
	ui.addressPlainTextEdit->setPlainText(emptyStr);
	m_dataModel->removeRows(0, m_dataModel->rowCount());
	ui.cellLineEdit->setText(emptyStr);
	ui.consumeLcdNumber->display(0);
	ui.depositLcdNumber->display(0);
	ui.descPlainTextEdit->setPlainText(emptyStr);
	ui.idLcdNumber->display(0);
	ui.levelComboBox->setCurrentIndex(0);
	ui.nameLineEdit->setText(emptyStr);
	ui.phoneLineEdit->setText(emptyStr);
	ui.sexComboBox->setCurrentIndex(SEX_UNDEFINE);
	ui.timesLcdNumber->display(0);
}

void CustomerDetailWidget::clearPicture() {
	m_customerPicData.clear();
	ui.imageLabel->setPixmap(m_zeroPicture);
}

void CustomerDetailWidget::displayPicture(QByteArray& data){
	m_customerPicData.clear();
	m_customerPicData = data;
	if(!m_customerPicData.isEmpty()) {
		QPixmap pic;
		pic.loadFromData(m_customerPicData);
		if(pic.height() != 0) {
			uint32 picAspect = pic.width()/pic.height();
			uint32 labelAspect = ui.imageLabel->width()/ui.imageLabel->height();
			if(picAspect > labelAspect) {
				pic = pic.scaledToWidth
					(ui.imageLabel->width(), Qt::SmoothTransformation);
			} else {
				pic = pic.scaledToHeight
					(ui.imageLabel->height(), Qt::SmoothTransformation);
			}
			ui.imageLabel->setPixmap(pic);
		} else {
			ui.imageLabel->setPixmap(m_zeroPicture);
		}
	} else {
		ui.imageLabel->setPixmap(m_zeroPicture);
	}
}


void CustomerDetailWidget::editCustomer(Customer* data){
	if(0 == ui.idLcdNumber->intValue()) {
		MessageBox::showMessageBox
			(this, QMessageBox::Warning, cmString, zeroSelectionWarning);
		return;
	}
	if(CUSTOMER_NEW == m_mode) {		
		MessageBox::showMessageBox
			(this, QMessageBox::Warning, cmString, cmCustomerCannotEditWarning);
		return;
	}
	if(NULL != data) {
		browseCustomer(data);
	}
	changeMode(CUSTOMER_MODIFY);
}


void CustomerDetailWidget::newCustomer(){
	if(CUSTOMER_MODIFY == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox
			(this, QMessageBox::Question, cmString, abandonModifyWarning))
			return;
	}
	if(CUSTOMER_NEW == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox
			(this, QMessageBox::Question, cmString, cmCustomerEditModeWarning))
			return;
	}
	clearData();
	changeMode(CUSTOMER_NEW);
}


void CustomerDetailWidget::setCustomerLevels(list<CustomerLevel>* data){
	ui.levelComboBox->clear();
	ui.levelComboBox->addItem(LOCAL8BITSTR(undefineStr), 0);
	list<CustomerLevel>::iterator it = data->begin();
	while(data->end() != it)
	{
		ui.levelComboBox->addItem(LOCAL8BITSTR(it->getName().c_str()), 
			QVariant(it->getId()));
		it++;
	}
}


void CustomerDetailWidget::submit(){
	if(ui.nameLineEdit->text().isEmpty() || 
		SEX_UNDEFINE == ui.sexComboBox->itemData
		(ui.sexComboBox->currentIndex()).toUInt()) {
		MessageBox::showMessageBox
			(this, QMessageBox::Warning, cmString, cmEmptyNameSexWarnning);
		return;
	}
	Customer* data = new Customer();

	data->setaddress
		(ui.addressPlainTextEdit->toPlainText().toLocal8Bit().data());
	data->setcell(ui.cellLineEdit->text().toLocal8Bit().data());
	data->setdescription
		(ui.descPlainTextEdit->toPlainText().toLocal8Bit().data());
	data->setid(ui.idLcdNumber->intValue());
	data->setname(ui.nameLineEdit->text().toLocal8Bit().data());
	data->setphone(ui.phoneLineEdit->text().toLocal8Bit().data());
	data->setsex(ui.sexComboBox->
		itemData(ui.sexComboBox->currentIndex()).toUInt());

	emit submittedCustomer(data, m_customerPicData, m_mode);
	changeMode(CUSTOMER_BROWSE);
}

void CustomerDetailWidget::changeMode(uint32 mode){
	m_mode = mode;
	switch(mode) {
		case CUSTOMER_BROWSE:
			{		 
				ui.addressPlainTextEdit->setReadOnly(true);
				ui.cellLineEdit->setReadOnly(true);
				ui.descPlainTextEdit->setReadOnly(true);
				ui.levelComboBox->setDisabled(true);
				ui.nameLineEdit->setReadOnly(true);
				ui.phoneLineEdit->setReadOnly(true);
				ui.sexComboBox->setDisabled(true);
				ui.line->setVisible(false);
				ui.picButton->setVisible(false);
				ui.submitButton->setVisible(false);
				break;
			}
		case CUSTOMER_MODIFY:
		case CUSTOMER_NEW:
			{
				ui.addressPlainTextEdit->setReadOnly(false);
				ui.cellLineEdit->setReadOnly(false);
				ui.descPlainTextEdit->setReadOnly(false);
				ui.levelComboBox->setDisabled(false);
				ui.nameLineEdit->setReadOnly(false);
				ui.phoneLineEdit->setReadOnly(false);
				ui.sexComboBox->setDisabled(false);
				ui.line->setVisible(true);
				ui.picButton->setVisible(true);
				ui.submitButton->setVisible(true);
				break;
			}
	}
}


void CustomerDetailWidget::selectPicture(){
	QString lastDir = 
		LOCAL8BITSTR(Singleton<AppParameter>::instance()->getLastDir().c_str());
	QString fileName = 
		QFileDialog::getOpenFileName(this, LOCAL8BITSTR(choosePicStr), 
		lastDir, LOCAL8BITSTR(imageFileStr));
	if(!fileName.isEmpty()) {
		std::string last = std::string(fileName.toLocal8Bit().data());
		last = last.substr(0, last.find_last_of(DIR_SEPERATOR));
		Singleton<AppParameter>::instance()->setLastDir(last);
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		if(file.size() > PIC_MAX_SIZE*MB) {
			QString warning = LOCAL8BITSTR(imageSizeWarning).arg(PIC_MAX_SIZE);
			MessageBox::showMessageBox
				(this, QMessageBox::Warning, cmString, warning.toLocal8Bit().data());
			return;
		}
		displayPicture(file.readAll());
		file.close();
	}
}