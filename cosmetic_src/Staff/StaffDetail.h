#ifndef STAFFDETAIL_H
#define STAFFDETAIL_H
class Staff;
#include <QtGui>
#include <list>
class Job;
class Level;
class Status;
using namespace std;

class StaffDetail : public QWidget
{
	Q_OBJECT

public:
	StaffDetail(QWidget *parent, int mode = 0);
	~StaffDetail();
	void SettingFont(QFont& font);
	void browseStaff(Staff* staff, bool myinfo = false);
	void modifyStaff(Staff* staff);
	void changeMode(int mode);
	void setJob(list<Job>* jobList);
	void setLevel(list<Level>* levelList);
	void setStatus(list<Status>* levelList);
	void displayPic(QByteArray& staff);

private:
	int m_mode;
	bool myinfo;
	void setupUi();
	QLabel *labelPortrait;
	QLineEdit *lineEditId;
	QLineEdit *lineEditName;
	QLabel *labelId;
	QLabel *labelName;
	QLabel *labelJob;
	QComboBox *comboBoxJob;
	QComboBox *comboBoxLevel;
	QLabel *labelLevel;
	QLabel *labelSex;
	QComboBox *comboBoxSex;
	QComboBox *comboBoxStatus;
	QLabel *labelStatus;
	QLineEdit *lineEditCell;
	QLabel *labelPhone;
	QLineEdit *lineEditPhone;
	QLabel *labelCell;
	QLabel *labelDescrption;
	QLabel *labelAddress;
	QPlainTextEdit *plainTextEditAddress;
	QPlainTextEdit *plainTextEditDescrption;
	QPushButton *pushButtonPix;
	QPushButton *pushButtonModify;
	QPushButton *pushButtonSubmmit;
	QToolTip *tip;
	QFont font;
	QPixmap noPic;
	QByteArray userPicData;

signals:
	void addedStaff(Staff* staff, QByteArray& pic);
	void modifiedStaff(Staff* staff, QByteArray& pic);

private slots:
	void modify();
	void selectPic();
	void submit();
	void newStaff();
};

#endif // STAFFDETAIL_H
