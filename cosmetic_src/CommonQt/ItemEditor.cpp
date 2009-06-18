#include "ItemEditor.h"
#include <QStandardItemModel>
#include "common.h"

ItemEditor::ItemEditor(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	if(NULL != parent) {
		move(parent->pos().x() + parent->width()/2 - width()/2, 
			parent->pos().y() + parent->height()/2 - height()/2);
	}
	
	m_DataModel = new QStandardItemModel(0, 0, this);
	m_column = m_DataModel->columnCount();
	ui.itemTable->setModel(m_DataModel);
}

ItemEditor::~ItemEditor()
{
	delete m_DataModel;
}

void ItemEditor::changeMode(ItemEditorMode mode)
{
	m_mode = mode;
	switch(m_mode) {
		case InitMode:
		{
			ui.submitButton->hide();
			ui.itemTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
			ui.itemTable->hideColumn(0);
			break;
		}
		case EditMode:
		{
			ui.submitButton->show();
			ui.addButton->show();
			ui.removeButton->show();
			ui.itemTable->setEditTriggers(QAbstractItemView::DoubleClicked |
										QAbstractItemView::SelectedClicked |
										QAbstractItemView::EditKeyPressed);
			ui.itemTable->hideColumn(0);
			break;
		}
		case DisplayMode:
		{
			ui.submitButton->hide();
			ui.addButton->hide();
			ui.removeButton->hide();
			ui.itemTable->setEditTriggers(QAbstractItemView::DoubleClicked |
										QAbstractItemView::SelectedClicked |
										QAbstractItemView::EditKeyPressed);
			ui.itemTable->showColumn(0);
			break;
		}
	}
}

void ItemEditor::appendColumn(int column)
{
	m_DataModel->insertColumns(m_DataModel->columnCount(), column);
	m_column = m_DataModel->columnCount();
}

void ItemEditor::add()
{
	ASSERT_POINTER(m_DataModel);
	int row = m_DataModel->rowCount();
	m_DataModel->insertRow(row);
	ui.itemTable->setRowHeight(row, 20);
}
void ItemEditor::remove()
{
	ASSERT_POINTER(m_DataModel);
	m_DataModel->removeRow(ui.itemTable->currentIndex().row());
}

void ItemEditor::submit()
{
	emit submitted(getData());
}

void ItemEditor::addData(int row, int column, const QVariant& data)
{
	ASSERT_POINTER(m_DataModel);
	if(column >= m_column) return;
	if(row >= m_DataModel->rowCount() || (0 == row && 0 == column)) {
		m_DataModel->insertRow(m_DataModel->rowCount());
	}
	int rowConvert = (0==row) ?  m_DataModel->rowCount()-1 : row;
	m_DataModel->setData(m_DataModel->index(rowConvert, column), data);
}

void ItemEditor::setHeaderData(int column, const QVariant& data)
{
	ASSERT_POINTER(m_DataModel);
	if(column >= m_column) return;
	m_DataModel->setHeaderData(column, Qt::Horizontal, data);
}

void ItemEditor::clearData()
{
	ASSERT_POINTER(m_DataModel);
	m_DataModel->removeRows(0, m_DataModel->rowCount());
}

void ItemEditor::hideColumn(int column)
{
	ui.itemTable->hideColumn(column);
}

void ItemEditor::setDelegate(int column, QAbstractItemDelegate * delegate)
{
	ui.itemTable->setItemDelegateForColumn(column, delegate);
}

void ItemEditor::setTitle(QString& title)
{
	ui.groupBox->setTitle(title);
}

