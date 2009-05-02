#include "ItemEditor.h"
#include <QStandardItemModel>

ItemEditor::ItemEditor(QWidget *parent, int mode)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_DataModel = NULL;
	m_mode = mode;
	if(InitMode == m_mode) {
		ui.submitButton->hide();
	}
}

ItemEditor::~ItemEditor()
{

}

void ItemEditor::init(int column)
{
	m_column = column;
	m_DataModel = new QStandardItemModel(0, m_column, this);
	ui.itemTable->setModel(m_DataModel);
}
void ItemEditor::add()
{
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
	m_DataModel->removeRow(ui.itemTable->currentIndex().row());
}

void ItemEditor::submit()
{
	emit submitted(getData());
}

void ItemEditor::addData(int row, int column, const QVariant& data)
{
	if(column >= m_column) return;
	if(row >= m_DataModel->rowCount())
		m_DataModel->insertRow(row);
	m_DataModel->setData(m_DataModel->index(row, column), data);
}

void ItemEditor::setHeaderData(int column, const QVariant& data)
{
	if(column >= m_column) return;
	m_DataModel->setHeaderData(column, Qt::Horizontal, data);
}

void ItemEditor::clearData()
{
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

