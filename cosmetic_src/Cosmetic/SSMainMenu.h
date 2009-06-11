#ifndef DARWINMAIN_H
#define DARWINMAIN_H

#include <QFrame>
#include "ui_SSMainMenu.h"

#include "DUIObserver.h"

class SSMainMenu : public QDialog, public DUIObserver
{
	Q_OBJECT

public:
	SSMainMenu(QWidget *parent = 0);
	~SSMainMenu();
	void OnEvent(Message& ev) ;
	void SettingFont(QFont& font);

private:
	void createIcons();
	void roundCorner();
	Ui::SSMenuWindowClass ui;


private slots:
	void startFunction(int x, int y);
//	void on_pushButtonLogoff_clicked();
};

#endif // DARWINMAIN_H
