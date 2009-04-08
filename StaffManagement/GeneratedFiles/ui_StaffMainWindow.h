/********************************************************************************
** Form generated from reading ui file 'StaffMainWindow.ui'
**
** Created: Wed Apr 8 12:48:01 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STAFFMAINWINDOW_H
#define UI_STAFFMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *comboBoxPattern;
    QLabel *labelKeyword;
    QLineEdit *lineEditKeyword;
    QLabel *label_3;
    QComboBox *comboBoxItem;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxSort;
    QCheckBox *checkBoxSearch;
    QTreeView *treeViewStaff;
    QPushButton *pushButtonBack;
    QPushButton *pushButtonLogoff;
    QPushButton *pushButtonExit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->setWindowModality(Qt::WindowModal);
    MainWindow->resize(572, 404);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(1);
    sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
    MainWindow->setSizePolicy(sizePolicy);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(30, 230, 261, 141));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(1);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy1);
    QFont font;
    font.setFamily(QString::fromUtf8("Tahoma"));
    font.setPointSize(9);
    font.setBold(false);
    font.setWeight(50);
    font.setKerning(true);
    groupBox->setFont(font);
    layoutWidget = new QWidget(groupBox);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 20, 242, 106));
    verticalLayout = new QVBoxLayout(layoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    formLayout = new QFormLayout();
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    formLayout->setSizeConstraint(QLayout::SetFixedSize);
    label = new QLabel(layoutWidget);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Tahoma"));
    font1.setPointSize(9);
    label->setFont(font1);

    formLayout->setWidget(0, QFormLayout::LabelRole, label);

    comboBoxPattern = new QComboBox(layoutWidget);
    comboBoxPattern->setObjectName(QString::fromUtf8("comboBoxPattern"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(comboBoxPattern->sizePolicy().hasHeightForWidth());
    comboBoxPattern->setSizePolicy(sizePolicy2);
    comboBoxPattern->setFont(font1);

    formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxPattern);

    labelKeyword = new QLabel(layoutWidget);
    labelKeyword->setObjectName(QString::fromUtf8("labelKeyword"));
    labelKeyword->setFont(font1);

    formLayout->setWidget(1, QFormLayout::LabelRole, labelKeyword);

    lineEditKeyword = new QLineEdit(layoutWidget);
    lineEditKeyword->setObjectName(QString::fromUtf8("lineEditKeyword"));
    lineEditKeyword->setFont(font1);

    formLayout->setWidget(1, QFormLayout::FieldRole, lineEditKeyword);

    label_3 = new QLabel(layoutWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
    label_3->setSizePolicy(sizePolicy3);
    label_3->setFont(font1);

    formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

    comboBoxItem = new QComboBox(layoutWidget);
    comboBoxItem->setObjectName(QString::fromUtf8("comboBoxItem"));
    sizePolicy2.setHeightForWidth(comboBoxItem->sizePolicy().hasHeightForWidth());
    comboBoxItem->setSizePolicy(sizePolicy2);
    comboBoxItem->setFont(font1);

    formLayout->setWidget(2, QFormLayout::FieldRole, comboBoxItem);


    verticalLayout->addLayout(formLayout);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    checkBoxSort = new QCheckBox(layoutWidget);
    checkBoxSort->setObjectName(QString::fromUtf8("checkBoxSort"));
    checkBoxSort->setFont(font1);

    horizontalLayout->addWidget(checkBoxSort);

    checkBoxSearch = new QCheckBox(layoutWidget);
    checkBoxSearch->setObjectName(QString::fromUtf8("checkBoxSearch"));
    checkBoxSearch->setFont(font1);

    horizontalLayout->addWidget(checkBoxSearch);


    verticalLayout->addLayout(horizontalLayout);

    treeViewStaff = new QTreeView(centralwidget);
    treeViewStaff->setObjectName(QString::fromUtf8("treeViewStaff"));
    treeViewStaff->setGeometry(QRect(40, 20, 471, 191));
    pushButtonBack = new QPushButton(centralwidget);
    pushButtonBack->setObjectName(QString::fromUtf8("pushButtonBack"));
    pushButtonBack->setGeometry(QRect(360, 250, 75, 23));
    pushButtonLogoff = new QPushButton(centralwidget);
    pushButtonLogoff->setObjectName(QString::fromUtf8("pushButtonLogoff"));
    pushButtonLogoff->setGeometry(QRect(360, 280, 75, 23));
    pushButtonExit = new QPushButton(centralwidget);
    pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));
    pushButtonExit->setGeometry(QRect(360, 310, 75, 23));
    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 572, 21));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

#ifndef QT_NO_SHORTCUT
    label->setBuddy(comboBoxPattern);
    labelKeyword->setBuddy(lineEditKeyword);
    label_3->setBuddy(comboBoxItem);
#endif // QT_NO_SHORTCUT


    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("MainWindow", "\351\200\211\351\241\271", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
    labelKeyword->setText(QApplication::translate("MainWindow", "\345\205\263\351\224\256\350\257\215", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\351\241\271", 0, QApplication::UnicodeUTF8));
    checkBoxSort->setText(QApplication::translate("MainWindow", "\346\216\222\345\272\217\345\277\275\347\225\245\345\244\247\345\260\217\345\206\231", 0, QApplication::UnicodeUTF8));
    checkBoxSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\345\277\275\347\225\245\345\244\247\345\260\217\345\206\231", 0, QApplication::UnicodeUTF8));
    pushButtonBack->setText(QApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", 0, QApplication::UnicodeUTF8));
    pushButtonLogoff->setText(QApplication::translate("MainWindow", "\346\263\250\351\224\200", 0, QApplication::UnicodeUTF8));
    pushButtonExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAFFMAINWINDOW_H
