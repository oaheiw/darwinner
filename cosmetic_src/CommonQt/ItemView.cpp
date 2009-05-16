#include "ItemView.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>
#include "common.h"

ItemView::ItemView(QWidget *parent)
:QWidget(parent)
{
	ui.setupUi(this);
	m_sortProxyModel = NULL;
	m_DataModel =new QStandardItemModel(0, 0, this);
	m_column = m_DataModel->columnCount();
	ui.itemList->setModel(m_DataModel);
}

ItemView::~ItemView()
{
	delete m_sortProxyModel;
	delete m_DataModel;
}

void ItemView::appendColumn(int column)
{
	m_DataModel->insertColumns(m_DataModel->columnCount(), column);
	m_column = m_DataModel->columnCount();
	ui.itemList->sortByColumn(0, Qt::AscendingOrder);
}


void ItemView::setProxy(QSortFilterProxyModel* proxy)
{
	m_sortProxyModel = proxy;
	m_sortProxyModel->setSourceModel(m_DataModel);
	m_sortProxyModel->setDynamicSortFilter(true);
	m_sortProxyModel->setFilterKeyColumn(-1);
	ui.itemList->setModel(m_sortProxyModel);
}

void ItemView::setTitle(QString& title)
{
	ui.groupBox->setTitle(title);
}

void ItemView::changeRegExp(QRegExp & exp)
{
	ASSERT_POINTER(m_sortProxyModel);
	m_sortProxyModel->setFilterRegExp(exp);

}

void ItemView::changeFilterColumn(int col)
{
	ASSERT_POINTER(m_sortProxyModel);
	m_sortProxyModel->setFilterKeyColumn(col);
}
void ItemView::changeSortCase(int caseSen)
{
	ASSERT_POINTER(m_sortProxyModel);
	m_sortProxyModel->setSortCaseSensitivity(Qt::CaseSensitivity(caseSen));
}

void ItemView::addData(int row, int column, const QVariant& data)
{
	if(column >= m_column) return;
	if(row >= m_DataModel->rowCount() || (0 == row && 0 == column)) {
		m_DataModel->insertRow(m_DataModel->rowCount());
	}
	int rowConvert = (0==row) ?  m_DataModel->rowCount()-1 : row;
	m_DataModel->setData(m_DataModel->index(rowConvert, column), data);
}

void ItemView::setHeaderData(int column, const QVariant& data)
{
	if(column >= m_column) return;
	m_DataModel->setHeaderData(column, Qt::Horizontal, data);
}

void ItemView::clearData()
{
	m_DataModel->removeRows(0, m_DataModel->rowCount());
}

void ItemView::getActivatedItem(const QModelIndex& data)
{
	emit itemActivated(data.row(), data.column(), data.data());
}

QVariant ItemView::sibling(int row, int column)
{
	QVariant data = ui.itemList->currentIndex().sibling(row,column).data();
	return data;
}

QVariant ItemView::currentIndex(int &row, int &column)
{
	row = ui.itemList->currentIndex().row();
	column = ui.itemList->currentIndex().column();
	return ui.itemList->currentIndex().data();
}

void ItemView::setColumnWidth(int column, int width)
{
	ui.itemList->setColumnWidth(column, width);
}

void ItemView::setDelegate(int column, QAbstractItemDelegate * delegate)
{
	ui.itemList->setItemDelegateForColumn(column, delegate);
}

