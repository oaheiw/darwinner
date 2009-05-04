#include "ItemEditor.h"
#include <QStandardItemModel>
#include "common.h"

ItemEditor::ItemEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_DataModel = new QStandardItemModel(0, 0, this);
	m_column = m_DataModel->columnCount();
	ui.itemTable->setModel(m_DataModel);
	setMode(EditMode);
}

ItemEditor::~ItemEditor()
{

}

void ItemEditor::setMode(ItemEditorMode mode)
{
	m_mode = mode;
	switch(m_mode) {
		case InitMode:
		{
			ui.submitButton->hide();
			break;
		}
		case EditMode:
		{
			ui.submitButton->show();
			ui.addButton->show();
			ui.removeButton->show();
			break;
		}
		case DisplayMode:
		{
			ui.submitButton->hide();
			ui.addButton->hide();
			ui.removeButton->hide();
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
	/*
	m_DataModel->setData(m_DataModel->index(row, 0), 0);
	m_DataModel->setData(m_DataModel->index(row, 1), "");
	m_DataModel->setData(m_DataModel->index(row, 2), 0);
	m_DataModel->setData(m_DataModel->index(row, 3), 0);
	m_DataModel->setData(m_DataModel->index(row, 4), "");
	*/
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
	if(row >= m_DataModel->rowCount())
		m_DataModel->insertRow(row);
	m_DataModel->setData(m_DataModel->index(row, column), data);
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
