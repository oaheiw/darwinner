#ifndef STAFFDETAIL_H
#define STAFFDETAIL_H
class Staff;
#include <QtGui>

class StaffDetail : public QWidget
{
	Q_OBJECT

public:
	StaffDetail(QWidget *parent, int mode = 0);
	~StaffDetail();
	void SettingFont(QFont& font);
	void browseStaff(Staff* staff);
	void modifyStaff(Staff* staff);
	void changeMode(int mode);

private:
	int m_mode;
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

signals:
	void addedStaff(Staff*);
	void modifiedStaff(Staff*);

private slots:
	void modify();
	void selectPic();
	void submit();
	void newStaff();
};

#endif // STAFFDETAIL_H
