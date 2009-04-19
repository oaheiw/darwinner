#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QWidget>
#include "ui_PasswordWidget.h"
#include <string>
using namespace std;
using namespace Ui;

class PasswordWidget : public QWidget, public PasswordWidgetClass
{
	Q_OBJECT

public:
	PasswordWidget(QWidget *parent = 0);
	~PasswordWidget();
signals:
	void submitPassword(string oldpw, string newpw);
private slots:
	void checkInput();
	void submit();
};

#endif // PASSWORDWIDGET_H
