#include "BusinessDetailWidget.h"
#include "Singleton.h"
#include "AppParameter.h"
#include <QFileDialog>
#include <QFile>
#include "MessageBox.h"
#include "UiStrings.h"
#include "Business.h"
#include "BusinessType.h"
#include <QByteArray>

BusinessDetailWidget::BusinessDetailWidget(QWidget *parent, uint32 mode)
	: QWidget(parent),m_mode(mode)
{
	m_businessPicData.clear();
	ui.setupUi(this);
	changeMode(m_mode);
	connect(ui.picButton, SIGNAL(clicked()), this, SLOT(selectPicture()));
	connect(ui.submitButton, SIGNAL(clicked()), this, SLOT(submit()));
	m_zeroPicture = QPixmap(":/business/business").
		scaled(ui.imageLabel->width(), ui.imageLabel->height(), 
		Qt::KeepAspectRatio ,Qt::SmoothTransformation);
	displayPicture(m_businessPicData);
}

BusinessDetailWidget::~BusinessDetailWidget()
{

}



void BusinessDetailWidget::browseBusiness(Business* data){
	if(BUSINESS_NEW == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, 
			bmString, bmBusinessEditModeWarning))
			return;
	}
	if(BUSINESS_MODIFY == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, 
			bmString, abandonModifyWarning))
			return;
	}
	changeMode(BUSINESS_BROWSE);
	ui.adjustableCheckBox->setChecked(data->getAdjustable());
	ui.brandLineEdit->setText(LOCAL8BITSTR(data->brand().c_str()));
	ui.buysLcdNumber->display(QString::number(data->buys()));
	ui.costSpinBox->setValue(data->cost());
	ui.descPlainTextEdit->setPlainText(LOCAL8BITSTR(data->description().c_str()));
	ui.discountSpinBox->setValue(data->discount());
	ui.dualDiscountCheckBox->setChecked(data->isDualDiscoutn());
	ui.idLcdNumber->display(QString::number(data->id()));
	ui.nameLineEdit->setText(LOCAL8BITSTR(data->name().c_str()));
	ui.priceSpinBox->setValue(data->price());
	ui.salesLcdNumber->display(QString::number(data->sales()));
	ui.specLineEdit->setText(LOCAL8BITSTR(data->specification().c_str()));
	ui.stocksLcdNumber->display(QString::number(data->stocks()));
	ui.typeComboBox->setCurrentIndex(ui.typeComboBox->findData(data->type()));
	int h = ((double)(data->getRating())/(double)(ui.progressBar->maximum()))*COLOR_GREEN;
	QPalette palette = ui.progressBar->palette();
	palette.setColor(QPalette::Normal, QPalette::Highlight, QColor::fromHsv(h, 255, 255));
	ui.progressBar->setPalette(palette);
	ui.progressBar->setValue(data->getRating());
}

void BusinessDetailWidget::clearData() {
	ui.adjustableCheckBox->setChecked(false);
	ui.brandLineEdit->setText(emptyStr);
	ui.buysLcdNumber->display(0);
	ui.costSpinBox->setValue(0);
	ui.descPlainTextEdit->setPlainText(emptyStr);
	ui.discountSpinBox->setValue(100);
	ui.dualDiscountCheckBox->setChecked(false);
	ui.idLcdNumber->display(0);
	ui.nameLineEdit->setText(emptyStr);
	ui.priceSpinBox->setValue(0);
	ui.progressBar->setValue(0);
	ui.salesLcdNumber->display(0);
	ui.specLineEdit->setText(emptyStr);
	ui.stocksLcdNumber->display(0);
	ui.typeComboBox->setCurrentIndex(0);
}

void BusinessDetailWidget::clearPicture() {
	m_businessPicData.clear();
	ui.imageLabel->setPixmap(m_zeroPicture);
}

void BusinessDetailWidget::displayPicture(QByteArray& data){
	m_businessPicData.clear();
	m_businessPicData = data;
	if(!m_businessPicData.isEmpty()) {
		QPixmap pic;
		pic.loadFromData(m_businessPicData);
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


void BusinessDetailWidget::editBusiness(Business* data){
	if(0 == ui.idLcdNumber->intValue()) {
		MessageBox::showMessageBox(this, QMessageBox::Warning, bmString, zeroSelectionWarning);
		return;
	}
	if(BUSINESS_NEW == m_mode) {		
		MessageBox::showMessageBox(this, QMessageBox::Warning, bmString, bmBusinessCannotEditWarning);
		return;
	}
	if(NULL != data) {
		browseBusiness(data);
	}
	changeMode(BUSINESS_MODIFY);
}


void BusinessDetailWidget::newBusiness(){
	if(BUSINESS_MODIFY == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, 
			bmString, abandonModifyWarning))
			return;
	}
	if(BUSINESS_NEW == m_mode) {		
		if(QMessageBox::No == MessageBox::showMessageBox(this, QMessageBox::Question, 
			bmString, bmBusinessEditModeWarning))
				return;
	}
	clearData();
	changeMode(BUSINESS_NEW);
}


void BusinessDetailWidget::setBusinessTypes(list<BusinessType>* types){
	ui.typeComboBox->clear();
	ui.typeComboBox->addItem(LOCAL8BITSTR(undefineStr), 0);
	list<BusinessType>::iterator it = types->begin();
	while(types->end() != it)
	{
		ui.typeComboBox->addItem(LOCAL8BITSTR(it->getName().c_str()), QVariant(it->getId()));
		it++;
	}
}


void BusinessDetailWidget::submit(){
	if(ui.nameLineEdit->text().isEmpty() || 
		0 == ui.typeComboBox->currentIndex()) {
		MessageBox::showMessageBox
			(this, QMessageBox::Warning, bmString, bmEmptyNameTypeWarnning);
		return;
	}
	Business* data = new Business();
	data->setAdjustable(ui.adjustableCheckBox->isChecked());
	data->setBrand(ui.brandLineEdit->text().toLocal8Bit().data());
	data->setCost(ui.costSpinBox->value());
	data->setDescription(ui.descPlainTextEdit->toPlainText().toLocal8Bit().data());
	data->setDiscount(ui.discountSpinBox->value());
	data->setDualDiscoutn(ui.dualDiscountCheckBox->isChecked());
	data->setName(ui.nameLineEdit->text().toLocal8Bit().data());
	data->setPrice(ui.priceSpinBox->value());
	data->setSpecification(ui.specLineEdit->text().toLocal8Bit().data());
	data->setType(ui.typeComboBox->itemData(ui.typeComboBox->currentIndex()).toUInt());
	data->setId(ui.idLcdNumber->intValue());
	emit submittedBusiness(data, m_businessPicData, m_mode);
	changeMode(BUSINESS_BROWSE);
}

void BusinessDetailWidget::changeMode(uint32 mode){
	m_mode = mode;
	switch(mode) {
		case BUSINESS_BROWSE:
			{		 
				ui.adjustableCheckBox->setDisabled(true);
				ui.brandLineEdit->setReadOnly(true);
				ui.costSpinBox->setReadOnly(true);
				ui.descPlainTextEdit->setReadOnly(true);
				ui.discountSpinBox->setReadOnly(true);
				ui.dualDiscountCheckBox->setDisabled(true);
				ui.nameLineEdit->setReadOnly(true);
				ui.priceSpinBox->setReadOnly(true);
				ui.specLineEdit->setReadOnly(true);
				ui.typeComboBox->setDisabled(true);
				ui.line->setVisible(false);
				ui.picButton->setVisible(false);
				ui.submitButton->setVisible(false);
				break;
			}
		case BUSINESS_MODIFY:
		case BUSINESS_NEW:
			{
				ui.adjustableCheckBox->setDisabled(false);
				ui.brandLineEdit->setReadOnly(false);
				ui.costSpinBox->setReadOnly(false);
				ui.descPlainTextEdit->setReadOnly(false);
				ui.discountSpinBox->setReadOnly(false);
				ui.dualDiscountCheckBox->setDisabled(false);
				ui.nameLineEdit->setReadOnly(false);
				ui.priceSpinBox->setReadOnly(false);
				ui.specLineEdit->setReadOnly(false);
				ui.typeComboBox->setDisabled(false);
				ui.line->setVisible(true);
				ui.picButton->setVisible(true);
				ui.submitButton->setVisible(true);
				break;
			}
	}
}


void BusinessDetailWidget::selectPicture(){
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
			MessageBox::showMessageBox(this, QMessageBox::Warning, bmString, warning.toLocal8Bit().data());
			return;
		}
		displayPicture(file.readAll());
		file.close();
	}
}