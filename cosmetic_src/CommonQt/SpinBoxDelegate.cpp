#include <QtGui>
#include <QSpinBox>
#include <QModelIndex>
#include "SpinBoxDelegate.h"



SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
:QItemDelegate(parent), m_max(0), m_min(0), m_prefix(""),m_suffix("")
{
	
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
	QSpinBox* editor = new QSpinBox(parent);
	editor->setRange(m_min, m_max);
	editor->setSuffix(LOCAL8BITSTR(m_suffix.c_str()));
	editor->setPrefix(LOCAL8BITSTR(m_prefix.c_str()));
	return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	int value = spinBox->value();
	model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void SpinBoxDelegate::setRange(uint32 min, uint32 max){
	m_max = max;
	m_min = min;
}

void SpinBoxDelegate::setPrefix(string& newVal){

	m_prefix = newVal;
}

void SpinBoxDelegate::setSuffix(string& newVal){

	m_suffix = newVal;
}