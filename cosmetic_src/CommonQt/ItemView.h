#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include "ui_ItemView.h"
class QAbstractItemModel;
class QSortFilterProxyModel;

class ItemView : public QWidget
{
	Q_OBJECT

public:
	ItemView(/*int column, */QWidget *parent = 0);
	~ItemView();
	void setProxy(QSortFilterProxyModel* proxy);
	void setTitle(QString& title);
	void addData(int row, int column, const QVariant& data);
	void setHeaderData(int column, const QVariant& data);
	void clearData();
	void appendColumn(int column);
	QVariant sibling(int row, int column);
	QVariant currentIndex(int &row, int &column);
	void setColumnWidth(int column, int width);

protected:
	Ui::ItemViewClass ui;

private:
	int m_column;
	QAbstractItemModel* m_DataModel;
	QSortFilterProxyModel* m_sortProxyModel;

signals:
	void itemActivated(int row, int column, QVariant& data);

private slots:
	void changeRegExp(QRegExp & exp);
	void changeFilterColumn(int col);
	void changeSortCase(int caseSen);
	void getActivatedItem(const QModelIndex&);
};

#endif // ITEMVIEW_H
