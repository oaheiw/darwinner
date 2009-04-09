#ifndef STAFFMANAGEMENT_H
#define STAFFMANAGEMENT_H

#include "staffmanagement_global.h"
#include "DUIObserver.h"
#include "Staff.h"
#include <QtGui>
#include <QEvent>
#include <QFont>
#include <list>
using namespace std;

class STAFFMANAGEMENT_EXPORT StaffManagementUI : public QMainWindow, public DUIObserver
{
	Q_OBJECT
public:
	StaffManagementUI();
	~StaffManagementUI();
	void OnEvent(Message& Msg);
	void SettingFont(QFont& font);

protected:
	void showEvent ( QShowEvent * event );
	void closeEvent ( QCloseEvent * event );
	void setupUi();

private:
	void addStaff(list<Staff> *staffList);

//ui items
	QAction *actionExport;
    QAction *actionMenu;
    QAction *actionLogOff;
    QAction *actionExit;
    QTreeView *treeViewStaff;
    QComboBox *comboBoxPattern;
    QLabel *labelSearchPattern;
    QLineEdit *lineEditKeyword;
    QLabel *labelKeyword;
    QComboBox *comboBoxItem;
    QLabel *labelSearchItem;
    QCheckBox *checkBoxSort;
    QCheckBox *checkBoxSearch;
    QMenuBar *menubar;
    QMenu *menu_File;
	QMenu *menu_Display;
	QMenu *menu_Setting;
	QMenu *menu_About;
    QStatusBar *statusbar;
	QGroupBox *staffGroupBox;
	QGroupBox *optionGroupBox;
	QWidget *customCentralWidget;

//data items;
	QAbstractItemModel* m_stuffDataModel;
	QSortFilterProxyModel* m_sortProxyModel;

private slots:
	void Exit();
	void Logoff();
	void Menu();

     void filterRegExpChanged();
     void filterColumnChanged();
     void sortChanged();
};

#endif // STUFFMANAGEMENT_H
