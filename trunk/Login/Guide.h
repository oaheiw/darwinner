 #ifndef GUIDE_H
 #define GUIDE_H

#include <QWizard>
class JobTypeWidget;
class LevelWidget;

class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
#include "DUIObserver.h"
class Message;

 class Guide : public QWizard , public DUIObserver
 {
     Q_OBJECT

 public:
     Guide(QWidget *parent = 0);
	 void OnEvent(Message& ev) ;
     void accept();

 private:
 	Message* m_message;
	LevelWidget* level;
	JobTypeWidget* job;
 };

 class IntroPage : public QWizardPage
 {
     Q_OBJECT

 public:
     IntroPage(QWidget *parent = 0);

 private:
     QLabel *label;
 };

 class SupperUserPage : public QWizardPage
 {
     Q_OBJECT

 public:
     SupperUserPage(QWidget *parent = 0);
	 virtual bool isComplete () const;

 private:
     QLabel *passwordLabel;
     QLabel *confirmLabel;
     QLineEdit *passwordLineEdit;
     QLineEdit *confirmLineEdit;
 };

 class StaffInfoPage : public QWizardPage
 {
     Q_OBJECT

 public:
     StaffInfoPage(LevelWidget* level, JobTypeWidget* job, QWidget *parent = 0);

 protected:
     void initializePage();

 private:
	LevelWidget* level;
	JobTypeWidget* job;
	QLabel* jobLabel;
	QLabel* levelLabel;
 };

 class StaffRightsPage : public QWizardPage
 {
     Q_OBJECT

 public:
     StaffRightsPage(QWidget *parent = 0);

 protected:
     void initializePage();

 private:
     QLabel *outputDirLabel;
     QLabel *headerLabel;
     QLabel *implementationLabel;
     QLineEdit *outputDirLineEdit;
     QLineEdit *headerLineEdit;
     QLineEdit *implementationLineEdit;
 };

 class ConclusionPage : public QWizardPage
 {
     Q_OBJECT

 public:
     ConclusionPage(QWidget *parent = 0);

 protected:
     void initializePage();

 private:
     QLabel *label;
 };

 #endif