#include "MessageBox.h"
#include <QAbstractButton>

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
	messageBox.setFont(QFont("SimSun", 9));
	messageBox.setWindowTitle(QString::fromLocal8Bit(windowTitle.c_str()));
	messageBox.setIcon(icon);
	messageBox.setText(QString::fromLocal8Bit(title.c_str()));
	messageBox.setInformativeText(QString::fromLocal8Bit(info.c_str()));
	if(QMessageBox::Information == icon) {
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("返回"));
	}
	if(QMessageBox::Question == icon) {
		messageBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
		messageBox.setDefaultButton(QMessageBox::No);
		messageBox.button(QMessageBox::Yes)->setText(QString::fromLocal8Bit("确定"));
		messageBox.button(QMessageBox::No)->setText(QString::fromLocal8Bit("取消"));
	}
	if(QMessageBox::Critical == icon) {
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("返回"));
	}
	return (QMessageBox::StandardButton)messageBox.exec();
 }

