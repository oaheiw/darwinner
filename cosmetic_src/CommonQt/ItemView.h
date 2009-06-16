#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include "ui_ItemView.h"
#include <QString>
#include <QRegExp>
#include <QDate>
class QAbstractItemModel;
class QSortFilterProxyModel;
class QAbstractItemDelegate;

class ItemView : public QWidget
{
	Q_OBJECT

public:
	enum VIEWMODE {
		SIMPLEVIEW,
		SIMPLEVIEW_SEARCH,
		SIMPLEVIEW_DATEBOX,
		SIMPLEVIEW_BOTH,
		CHECKBOXVIEW,
		CHECKBOXVIEW_SEARCH,
		CHECKBOXVIEW_DATEBOX,
		CHECKBOXVIEW_BOTH,
		FULLVIEW
	};
	ItemView(QWidget *parent = 0, short mode = CHECKBOXVIEW_SEARCH);
	~ItemView();

	void clearData();
	QVariant sibling(int row, int column);
	QVariant currentIndex(int &row, int &column);
	void setAutoResize(bool bAuto);


protected:
	void changeMode(short mode);
	void appendColumn(int column);
	void addData(int row, int column, const QVariant& data);
	void setHeaderData(int column, const QVariant& data);
	void setProxy(QSortFilterProxyModel* proxy);
	void setTitle(QString& title);
	void setColumnWidth(int column, int width);
	void setDelegate(int column, QAbstractItemDelegate* delegate);
	void setButtonsVisable(bool show);
	Ui::ItemViewClass ui;

private:
	short m_mode;
	int m_column;
	QAbstractItemModel* m_DataModel;
	QSortFilterProxyModel* m_sortProxyModel;
	void setOperationBoxVisable(bool show);
	void setSearchBoxVisable(bool show);
	void setDateBoxVisable(bool show);
	void setCheckBoxVisable(bool show);
	QString m_keyword;
	int m_filterColumn;
	QRegExp m_searchRegExp;
	QDate m_from;
	QDate m_to;

signals:
	void itemActivated(int row, int column, QVariant& data);

private slots:
	void changeRegExp(QRegExp & exp);
	void changeFilterColumn(int col);
	void changeSortCase(int caseSen);
	void changeDateRange(QDate& from, QDate& to);
	void getActivatedItem(const QModelIndex&);
	//for own filters
	void keywordChanged(QString keyword);
	void filterItemChanged(int item);
	void fromDateChanged(QDate from);
	void toDateChanged(QDate to);
};

#endif // ITEMVIEW_H
