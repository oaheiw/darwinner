#include "MessageBox.h"
#include <QAbstractButton>
#include "UiStrings.h"
using namespace UiStr;

MessageBox::MessageBox(QWidget *parent)
	: QMessageBox(parent)
{

}

MessageBox::~MessageBox()
{

}

 QMessageBox::StandardButton MessageBox::showMessageBox(QWidget * parent, QMessageBox::Icon icon, string windowTitle, string title, string info)
 {
 	QMessageBox messageBox(parent);
//	messageBox.setFont(QFont("SimSun", 9));
	messageBox.setWindowTitle(LOCAL8BITSTR(windowTitle.c_str()));
	messageBox.setIcon(icon);
	messageBox.setText(LOCAL8BITSTR(title.c_str()));
	messageBox.setInformativeText(LOCAL8BITSTR(info.c_str()));
	if(QMessageBox::Information == icon) {
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.button(QMessageBox::Ok)->setText(LOCAL8BITSTR(backStr));
	}
	if(QMessageBox::Question == icon) {
		messageBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
		messageBox.setDefaultButton(QMessageBox::No);
		messageBox.button(QMessageBox::Yes)->setText(LOCAL8BITSTR(okStr));
		messageBox.button(QMessageBox::No)->setText(LOCAL8BITSTR(cancleStr));
	}
	if(QMessageBox::Critical == icon) {
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.button(QMessageBox::Ok)->setText(LOCAL8BITSTR(backStr));
	}
	if(QMessageBox::Warning== icon) {
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.button(QMessageBox::Ok)->setText(LOCAL8BITSTR(backStr));
	}
	return (QMessageBox::StandardButton)messageBox.exec();
 }

