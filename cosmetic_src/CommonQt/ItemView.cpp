#include "ItemView.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>
#include "common.h"
#include <QDate>
#include "UiStrings.h"

ItemView::ItemView(QWidget *parent, short mode)
:QWidget(parent),m_mode(mode),m_filterColumn(-1),m_keyword("")
,m_to(QDateTime::currentDateTime().date())
{
	ui.setupUi(this);
	changeMode(m_mode);
	m_from = m_to.addMonths(-1);
	ui.fromDateEdit->setDate(m_from);
	ui.toDateEdit->setDate(m_to);
	ui.itemComboBox->addItem(LOCAL8BITSTR(allItemStr), -1);
	m_searchRegExp = QRegExp(m_keyword, Qt::CaseInsensitive, QRegExp::RegExp);
	m_sortProxyModel = NULL;

	if(SIMPLEVIEW == m_mode || SIMPLEVIEW_SEARCH == m_mode || 
		SIMPLEVIEW_DATEBOX == m_mode || SIMPLEVIEW_BOTH == m_mode) {
			m_DataModel =new QStandardItemModel(0, 0, this);
	} else {
		m_DataModel =new QStandardItemModel(0, 0, this);
	}
	m_column = m_DataModel->columnCount();
	ui.itemList->setModel(m_DataModel);

	connect(ui.keywordLineEdit, SIGNAL(textChanged(QString)), 
		this, SLOT(keywordChanged(QString)));
	connect(ui.itemComboBox, SIGNAL(currentIndexChanged(int)), 
		this, SLOT(filterItemChanged(int)));
	connect(ui.fromDateEdit, SIGNAL(dateChanged(QDate)), 
		this, SLOT(fromDateChanged(QDate)));
	connect(ui.toDateEdit, SIGNAL(dateChanged(QDate)), 
		this, SLOT(toDateChanged(QDate)));
}

ItemView::~ItemView()
{
	clearData();
	delete m_sortProxyModel;
	delete m_DataModel;
}

void ItemView::changeMode(short mode)
{
	m_mode = mode;
	switch(mode) {
		case SIMPLEVIEW:
			{
				setOperationBoxVisable(false);
				break;
			}
		case SIMPLEVIEW_SEARCH:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(false);
				setDateBoxVisable(false);
				setSearchBoxVisable(true);
				break;
			}
		case SIMPLEVIEW_DATEBOX:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(false);
				setDateBoxVisable(true);
				setSearchBoxVisable(false);
				break;
			}
		case SIMPLEVIEW_BOTH:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(false);
				setDateBoxVisable(true);
				setSearchBoxVisable(true);
				break;
			}
		case CHECKBOXVIEW:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(true);
				setSearchBoxVisable(false);
				setDateBoxVisable(false);
				break;
			}
		case CHECKBOXVIEW_SEARCH:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(true);
				setSearchBoxVisable(true);
				setDateBoxVisable(false);
				break;
			}
		case CHECKBOXVIEW_DATEBOX:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(true);
				setSearchBoxVisable(false);
				setDateBoxVisable(true);
				break;
			}
		case CHECKBOXVIEW_BOTH:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(true);
				setSearchBoxVisable(true);
				setDateBoxVisable(true);
				break;
			}
		case FULLVIEW:
		default:
			{
				setOperationBoxVisable(true);
				setCheckBoxVisable(true);
				setButtonsVisable(true);
				setSearchBoxVisable(true);
				setDateBoxVisable(true);
				break;
			}
	}
}

void ItemView::setOperationBoxVisable(bool show)
{
	ui.operationBox->setVisible(show);
}

void ItemView::setSearchBoxVisable(bool show)
{
	ui.keywordLineEdit->setVisible(show);
	ui.itemComboBox->setVisible(show);
	ui.keywordLabel->setVisible(show);
	ui.at1Label->setVisible(show);
	ui.at2Label->setVisible(show);
	if(show)
		ui.horizontalSpacer_2->changeSize(10, 20);
	else
		ui.horizontalSpacer_2->changeSize(0, 20);

}
void ItemView::setDateBoxVisable(bool show)
{
	ui.fromLabel->setVisible(show);
	ui.fromDateEdit->setVisible(show);
	ui.toLabel->setVisible(show);
	ui.toDateEdit->setVisible(show);
}

void ItemView::setCheckBoxVisable(bool show)
{
	ui.selectAllcheckBox->setVisible(show);
	ui.invertSlelctcheckBox->setVisible(show);
}

void ItemView::setButtonsVisable(bool show)
{
	ui.exportButton->setVisible(show);
	ui.printButton->setVisible(show);
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
	ui.itemList->setModel(m_sortProxyModel);
	changeRegExp(m_searchRegExp);
	changeFilterColumn(m_filterColumn);
	changeSortCase(Qt::CaseInsensitive);
}

/**
 * void ItemView::setDataModel(QAbstractItemModel* data) { m_DataModel = data;
 * if(NULL != m_sortProxyModel) { ui.itemList->setModel(m_sortProxyModel); } else
 * { ui.itemList->setModel(m_DataModel); } }
 */
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

void ItemView::changeDateRange(QDate& from, QDate& to)
{
	ASSERT_POINTER(m_sortProxyModel);
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
	ui.itemComboBox->addItem(data.toString(), column);
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

void ItemView::keywordChanged(QString keyword)
{
	m_keyword = keyword;
	m_searchRegExp.setPattern(m_keyword);
	changeRegExp(m_searchRegExp);
}

void ItemView::filterItemChanged(int item)
{
	m_filterColumn = ui.itemComboBox->itemData(item).toInt();
	changeFilterColumn(m_filterColumn);
}

void ItemView::fromDateChanged(QDate date)
{
	if(date > QDateTime::currentDateTime().date())
		date = QDateTime::currentDateTime().date();
	if(date <= m_to) {
		m_from = date;
	} else {
		m_from = ui.toDateEdit->date();
	}
	ui.fromDateEdit->setDate(m_from);
	changeDateRange(m_from, m_to);
}

void ItemView::toDateChanged(QDate date)
{
	if(date > QDateTime::currentDateTime().date())
		date = QDateTime::currentDateTime().date();
	if(date >= m_from) {
		m_to = date;
	} else {
		m_to = ui.fromDateEdit->date();
	}
	ui.toDateEdit->setDate(m_to);
	changeDateRange(m_from, m_to);
}



void ItemView::setAutoResize(bool bAuto){
	if(bAuto){
		ui.itemList->header()->setResizeMode(QHeaderView::ResizeToContents);
	} else{
		ui.itemList->header()->setResizeMode(QHeaderView::Interactive);
	}
}