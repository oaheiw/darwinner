#ifndef STAFFMANAGEMENT_H
#define STAFFMANAGEMENT_H

#include "DUIObserver.h"
#include "Staff.h"
#include <QtGui>
#include <QEvent>
#include <QFont>
#include <vector>
class StaffDetail;
class QModelIndex;
using namespace std;

class StaffManagementUI : public QMainWindow, public DUIObserver
{
	Q_OBJECT
public:
	StaffManagementUI();
	~StaffManagementUI();
	void OnEvent(Message& Msg);
	void SettingFont(QFont& font);
	bool event(QEvent * ev);

protected:
	void setupUi();
	virtual bool eventFilter ( QObject * obj, QEvent * ev );
	void staffDetail(uint32 id);

private:
	void addStaff(std::vector<Staff> *staffList);

//ui items
	QAction *actionExport;
	QAction *actionMenu;
	QAction *actionLogOff;
	QAction *actionExit;
	QAction *actionStaffDetail;
	QAction *actionDeleteStaff;
	QAction *actionCasher4Client;
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
	StaffDetail* staffDetailWidget;

//data items;
	bool started;
	QFont font;
	QAbstractItemModel* m_stuffDataModel;
	QSortFilterProxyModel* m_sortProxyModel;

private slots:
	void Exit();
	void Logoff();
	void Menu();

	void filterRegExpChanged();
	void filterColumnChanged();
	void sortChanged();
	void staffActivated(const QModelIndex& item);
	void removeStaff();
	void cash4Client();
};

#endif // STUFFMANAGEMENT_H
