#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QWidget>
#include "ui_SearchBox.h"
#include <map>
using namespace std;

class SearchBox : public QWidget
{
	Q_OBJECT

public:
	SearchBox(QWidget *parent = 0);
	~SearchBox();
	void addFilterItem(QString& text);

signals:
	void regExpChanged(QRegExp &);
	void columnChanged(int);
	void sortChanged(int);

private:
	QString m_keyword;
	int m_pattern;
	int m_column;
	bool m_searchIgnoreCase;
	bool m_sortIgnoreCase;
	QRegExp m_searchRegExp;
	QRegExp::PatternSyntax m_syntax;
	Qt::CaseSensitivity m_searchCaseSensitivity;
	Qt::CaseSensitivity m_sortCaseSensitivity;
	map<int, int> m_regExpPatternMap;
	Ui::SearchBoxClass ui;

private slots:
	void keywordChange(QString keyword);
	void searchPatternChange(int pattern);
	void searchCaseChange(bool bCase);
	void searchItemChange(int item);
	void sortCaseChange(bool bCase);
};

#endif // SEARCHBOX_H
