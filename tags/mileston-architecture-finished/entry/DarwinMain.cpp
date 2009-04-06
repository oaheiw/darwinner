#include "DarwinMain.h"
#include "Singleton.cpp"
#include "MainDispatcher.h"
DarwinMain::DarwinMain(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

DarwinMain::~DarwinMain()
{

}


void DarwinMain::on_pushButtonLogoff_clicked()
{
	Singleton<MainDispatcher>::instance()->Logoff();
}

void DarwinMain::on_pushButtonStuffMgnt_clicked()
{
	Singleton<MainDispatcher>::instance()->StuffMgnt();
}