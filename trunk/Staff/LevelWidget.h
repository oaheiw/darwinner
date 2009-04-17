#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QtGui>
#include "ui_level.h"
#include <list>
#include "Level.h"
using namespace std;
class QFont;

class LevelWidget : public QWidget
{
	Q_OBJECT

public:
	LevelWidget(QWidget *parent = 0, int mode = 0);
	~LevelWidget();
	void settingFont(QFont& font);
	list<Level>* getLevelList();

private:
	Ui::Level ui;
	QAbstractItemModel* m_DataModel;
	int m_mode;

private slots:
	void add();
	void remove();
	void submit();
};

#endif // LEVELWIDGET_H
