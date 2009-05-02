#include "ItemView.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>

ItemView::ItemView(/*int column,*/QWidget *parent)
:QWidget(parent)
{
	ui.setupUi(this);
	m_sortProxyModel = NULL;
	m_DataModel = NULL;

	ui.itemList->setMouseTracking(true);
	ui.itemList->setRootIsDecorated(false);
	ui.itemList->setAlternatingRowColors(true);
	ui.itemList->setSortingEnabled(true);
	ui.itemList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.itemList->setContextMenuPolicy(Qt::DefaultContextMenu);
	ui.itemList->sortByColumn(0, Qt::AscendingOrder);
}

ItemView::~ItemView()
{
	delete m_sortProxyModel;
	delete m_DataModel;
}

void ItemView::initDataModel(int column)
{
	m_column = column;//for first selection column
	m_DataModel = new QStandardItemModel(0, m_column, parent());
	ui.itemList->setModel(m_DataModel);
}


void ItemView::setProxy(QSortFilterProxyModel* proxy)
{
	m_sortProxyModel = proxy;
	m_sortProxyModel->setSourceModel(m_DataModel);
	m_sortProxyModel->setDynamicSortFilter(true);
	m_sortProxyModel->setFilterKeyColumn(-1);
	ui.itemList->setModel(m_sortProxyModel);
}
/*
void ItemView::setDataModel(QAbstractItemModel* data)
{
	m_DataModel = data;
	if(NULL != m_sortProxyModel) {
		ui.itemList->setModel(m_sortProxyModel);
	} else {
		ui.itemList->setModel(m_DataModel);
	}
}
*/
void ItemView::setTitle(QString& title)
{
	ui.groupBox->setTitle(title);
}

void ItemView::changeRegExp(QRegExp & exp)
{
	if(NULL != m_sortProxyModel) {
		m_sortProxyModel->setFilterRegExp(exp);
	}
}

void ItemView::changeFilterColumn(int col)
{
	if(NULL != m_sortProxyModel) {
		m_sortProxyModel->setFilterKeyColumn(col);
	}
}
void ItemView::changeSortCase(int caseSen)
{
	if(NULL != m_sortProxyModel) {
		m_sortProxyModel->setSortCaseSensitivity(Qt::CaseSensitivity(caseSen));
	}
}

void ItemView::addData(int row, int column, const QVariant& data)
{
	if(column >= m_column) return;
	if(row >= m_DataModel->rowCount())
		m_DataModel->insertRow(row);
	m_DataModel->setData(m_DataModel->index(row, column), data);
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