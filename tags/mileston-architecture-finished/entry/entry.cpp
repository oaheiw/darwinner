#include "entry.h"
#include "MainDispatcher.h"
#include <string>
#include "Singleton.cpp"
#include "common.h"

entry::entry(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
}

entry::~entry()
{

}


void entry::on_pushButtonLogin_clicked()
{
	Singleton<MainDispatcher>::instance()->Login(ui.lineEditID->text().toStdString(), ui.lineEditPW->text().toStdString());
}