#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include "ui_ItemView.h"
class QAbstractItemModel;
class QSortFilterProxyModel;
class QAbstractItemDelegate;

class ItemView : public QWidget
{
	Q_OBJECT

public:
	ItemView(QWidget *parent = 0);
	~ItemView();

	void clearData();
	QVariant sibling(int row, int column);
	QVariant currentIndex(int &row, int &column);


protected:
	void appendColumn(int column);
	void addData(int row, int column, const QVariant& data);
	void setHeaderData(int column, const QVariant& data);
	void setProxy(QSortFilterProxyModel* proxy);
	void setTitle(QString& title);
	void setColumnWidth(int column, int width);
	void setDelegate(int column, QAbstractItemDelegate* delegate);
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
