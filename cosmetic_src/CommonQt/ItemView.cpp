#include "ItemView.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

ItemView::ItemView(/*int column,*/QWidget *parent)
:QWidget(parent)
{
	ui.setupUi(this);
//	m_column = column + 1;//for first selection column
	m_sortProxyModel = NULL;
	m_DataModel = NULL;//new QStandardItemModel(0, m_column, parent);

	ui.itemList->setMouseTracking(true);
	ui.itemList->setRootIsDecorated(false);
	ui.itemList->setAlternatingRowColors(true);
	ui.itemList->setSortingEnabled(true);
	ui.itemList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.itemList->setContextMenuPolicy(Qt::DefaultContextMenu);
	ui.itemList->installEventFilter(parent);
	ui.itemList->sortByColumn(1, Qt::AscendingOrder);
}

ItemView::~ItemView()
{
	delete m_sortProxyModel;
	delete m_DataModel;
}

void ItemView::initDataModel(int column)
{
	m_column = column + 1;//for first selection column
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
	if(column >= m_column -1) return;
	if(0 == column)//for first selection column
		m_DataModel->setData(m_DataModel->index(row, column), false);
	m_DataModel->setData(m_DataModel->index(row, column+1), data);
}

void ItemView::setHeaderData(int column, const QVariant& data)
{
	if(column >= m_column -1) return;
	if(0 == column)//for first selection column
		m_DataModel->setHeaderData(column, Qt::Horizontal, "");
	m_DataModel->setHeaderData(column+1, Qt::Horizontal, data);
}

void ItemView::clearData()
{
	m_DataModel->removeRows(0, m_DataModel->rowCount());
}

