#ifndef STAFFMANAGEMENT_H
#define STAFFMANAGEMENT_H

#include "DUIObserver.h"
class Staff;
#include <QtGui>
class QEvent;
#include <QFont>
#include <list>
#include <map>
#include <string>
class Job;
class Level;
class Status;
class StaffDetail;
class QModelIndex;
class StaffConfiguration;
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
	void getAllStaff();
	void getJobType();
	void getLevelType();
	void getStatusType();
	void removeStaff(uint32 id, string name);

private:
	void addStaff(std::list<Staff> *staffList);

	//ui items
	QAction *actionBrowseMyRecords;
	QAction *actionBrowseMyInfo;
	QAction *actionBrowseMySalary;
	QAction *actionChangeMyPassword;
	QAction *actionStaffConfig;
	QAction *actionAboutQt;
	QAction *actionAboutCosmetic;
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
	QMenu *menu_Personal;
	QMenu *menu_Setting;
	QMenu *menu_About;
	QStatusBar *statusbar;
	QGroupBox *staffGroupBox;
	QGroupBox *optionGroupBox;
	QGroupBox *infoGroupBox;
	QWidget *customCentralWidget;
	StaffDetail* staffDetailWidget;
	QPushButton *deletePushButton;
	QPushButton *addPushButton;
	QCheckBox *seletCheckBox;
	QMessageBox * messageBox;
	StaffConfiguration* config;
	
	//data items;
	bool started;
	QFont font;
	QAbstractItemModel* m_stuffDataModel;
	QSortFilterProxyModel* m_sortProxyModel;
	map<uint32, Level> m_staffLevel;
	map<uint32, Job> m_staffType;
	map<uint32, Status> m_staffState;

private slots:
	void Exit();
	void Logoff();
	void Menu();
	void addStaff(Staff* staff, QByteArray& image);
	void modifyStaff(Staff* staff, QByteArray& image);

	void filterRegExpChanged();
	void filterColumnChanged();
	void sortChanged();
	void staffActivated(const QModelIndex& item);
	void removeStaff();
	void cash4Client();
	void browseMyInfo();
	void changeMyPassword();
	void changePasswrod(string oldpw, string newpw);
	void setLevels(list<Level>* levels);
	void setJobs(list<Job>* jobs);
	void staffConfig();
};

#endif // STUFFMANAGEMENT_H
