/********************************************************************************
** Form generated from reading ui file 'StaffMainWindow.ui'
**
** Created: Wed Apr 8 20:00:29 2009
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
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExport;
    QAction *actionMenu;
    QAction *actionLogOff;
    QAction *actionExit;
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
    QMenuBar *menubar;
    QMenu *menu_File;
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
    QFont font;
    font.setFamily(QString::fromUtf8("Tahoma"));
    font.setPointSize(11);
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setWeight(50);
    font.setStrikeOut(false);
    MainWindow->setFont(font);
    actionExport = new QAction(MainWindow);
    actionExport->setObjectName(QString::fromUtf8("actionExport"));
    actionMenu = new QAction(MainWindow);
    actionMenu->setObjectName(QString::fromUtf8("actionMenu"));
    actionLogOff = new QAction(MainWindow);
    actionLogOff->setObjectName(QString::fromUtf8("actionLogOff"));
    actionExit = new QAction(MainWindow);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
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
    QFont font1;
    font1.setFamily(QString::fromUtf8("Tahoma"));
    font1.setPointSize(9);
    font1.setBold(false);
    font1.setWeight(50);
    font1.setKerning(true);
    groupBox->setFont(font1);
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
    QFont font2;
    font2.setFamily(QString::fromUtf8("Tahoma"));
    font2.setPointSize(9);
    label->setFont(font2);

    formLayout->setWidget(0, QFormLayout::LabelRole, label);

    comboBoxPattern = new QComboBox(layoutWidget);
    comboBoxPattern->setObjectName(QString::fromUtf8("comboBoxPattern"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(comboBoxPattern->sizePolicy().hasHeightForWidth());
    comboBoxPattern->setSizePolicy(sizePolicy2);
    comboBoxPattern->setFont(font2);

    formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxPattern);

    labelKeyword = new QLabel(layoutWidget);
    labelKeyword->setObjectName(QString::fromUtf8("labelKeyword"));
    labelKeyword->setFont(font2);

    formLayout->setWidget(1, QFormLayout::LabelRole, labelKeyword);

    lineEditKeyword = new QLineEdit(layoutWidget);
    lineEditKeyword->setObjectName(QString::fromUtf8("lineEditKeyword"));
    lineEditKeyword->setFont(font2);

    formLayout->setWidget(1, QFormLayout::FieldRole, lineEditKeyword);

    label_3 = new QLabel(layoutWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
    label_3->setSizePolicy(sizePolicy3);
    label_3->setFont(font2);

    formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

    comboBoxItem = new QComboBox(layoutWidget);
    comboBoxItem->setObjectName(QString::fromUtf8("comboBoxItem"));
    sizePolicy2.setHeightForWidth(comboBoxItem->sizePolicy().hasHeightForWidth());
    comboBoxItem->setSizePolicy(sizePolicy2);
    comboBoxItem->setFont(font2);

    formLayout->setWidget(2, QFormLayout::FieldRole, comboBoxItem);


    verticalLayout->addLayout(formLayout);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    checkBoxSort = new QCheckBox(layoutWidget);
    checkBoxSort->setObjectName(QString::fromUtf8("checkBoxSort"));
    checkBoxSort->setFont(font2);

    horizontalLayout->addWidget(checkBoxSort);

    checkBoxSearch = new QCheckBox(layoutWidget);
    checkBoxSearch->setObjectName(QString::fromUtf8("checkBoxSearch"));
    checkBoxSearch->setFont(font2);

    horizontalLayout->addWidget(checkBoxSearch);


    verticalLayout->addLayout(horizontalLayout);

    treeViewStaff = new QTreeView(centralwidget);
    treeViewStaff->setObjectName(QString::fromUtf8("treeViewStaff"));
    treeViewStaff->setGeometry(QRect(40, 20, 471, 191));
    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 572, 21));
    menu_File = new QMenu(menubar);
    menu_File->setObjectName(QString::fromUtf8("menu_File"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

#ifndef QT_NO_SHORTCUT
    label->setBuddy(comboBoxPattern);
    labelKeyword->setBuddy(lineEditKeyword);
    label_3->setBuddy(comboBoxItem);
#endif // QT_NO_SHORTCUT


    menubar->addAction(menu_File->menuAction());
    menu_File->addSeparator();
    menu_File->addAction(actionExport);
    menu_File->addSeparator();
    menu_File->addAction(actionMenu);
    menu_File->addAction(actionLogOff);
    menu_File->addAction(actionExit);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\221\230\345\267\245\347\256\241\347\220\206\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
    actionExport->setText(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
    actionMenu->setText(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    actionLogOff->setText(QApplication::translate("MainWindow", "LogOff", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("MainWindow", "\351\200\211\351\241\271", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
    labelKeyword->setText(QApplication::translate("MainWindow", "\345\205\263\351\224\256\350\257\215", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\351\241\271", 0, QApplication::UnicodeUTF8));
    checkBoxSort->setText(QApplication::translate("MainWindow", "\346\216\222\345\272\217\345\277\275\347\225\245\345\244\247\345\260\217\345\206\231", 0, QApplication::UnicodeUTF8));
    checkBoxSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\345\277\275\347\225\245\345\244\247\345\260\217\345\206\231", 0, QApplication::UnicodeUTF8));
    menu_File->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAFFMAINWINDOW_H
