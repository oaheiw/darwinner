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
	LevelWidget(QWidget *parent = 0, int mode = 1);
	~LevelWidget();
	void settingFont(QFont& font);
	list<Level>* getLevelList();
	void pushLevels(list<Level>* levels);

private:
	Ui::LevelUi ui;
	QAbstractItemModel* m_DataModel;
	int m_mode;

signals:
	void submitted(list<Level>* levellist);

private slots:
	void add();
	void remove();
	void submit();
};

#endif // LEVELWIDGET_H
