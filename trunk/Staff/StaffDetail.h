#ifndef STAFFDETAIL_H
#define STAFFDETAIL_H
class Staff;
#include <QtGui>

class StaffDetail : public QFrame
{
	Q_OBJECT

public:
	StaffDetail(QWidget *parent, int mode = 0, Staff* staff = 0);
	~StaffDetail();
	void SettingFont(QFont& font);
	void pushStaff(Staff* staff, int mode = 0);

private:
	int m_mode;
	Staff* m_staff;
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
	
};

#endif // STAFFDETAIL_H
