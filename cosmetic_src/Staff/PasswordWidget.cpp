#include "PasswordWidget.h"
#include "common.h"

PasswordWidget::PasswordWidget(QWidget *parent)
	: QWidget(parent, Qt::Popup)
{
	setupUi(this);
	oldLineEdit->setMaxLength(PW_MAX_LEN);
	newLineEdit->setMaxLength(PW_MAX_LEN);
	confirmLineEdit->setMaxLength(PW_MAX_LEN);
}

PasswordWidget::~PasswordWidget()
{

}

void PasswordWidget::checkInput()
{
	if(!oldLineEdit->text().isEmpty() && !newLineEdit->text().isEmpty() &&
		newLineEdit->text() == confirmLineEdit->text()) {
		submitPushButton->setEnabled(true);
	} else {
		submitPushButton->setEnabled(false);
	}
}

void PasswordWidget::submit() {
	emit submitPassword(oldLineEdit->text().toLocal8Bit().data(), newLineEdit->text().toLocal8Bit().data());
	close();
}
