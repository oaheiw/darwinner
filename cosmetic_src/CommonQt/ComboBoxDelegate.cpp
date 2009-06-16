///////////////////////////////////////////////////////////
//  ComboBoxDelegate.cpp
//  Implementation of the Class ComboBoxDelegate
//  Created on:      22-ÎåÔÂ-2009 12:07:58
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "ComboBoxDelegate.h"
#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>
#include "UiStrings.h"
#include "common.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
:QItemDelegate(parent)
{
	m_items.clear();
}



ComboBoxDelegate::~ComboBoxDelegate(){

}


QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
	QComboBox* editor = new QComboBox(parent);
	for(QMap<uint32, string>::const_iterator it = m_items.begin() ; 
		m_items.end() != it ; it++)
		editor->addItem(LOCAL8BITSTR(it.value().c_str()), it.key());
	return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	uint32 value = index.model()->data(index, Qt::EditRole).toUInt();
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	comboBox->setCurrentIndex(comboBox->findData(value));
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	uint32 value = comboBox->itemData(comboBox->currentIndex()).toUInt();
	model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void ComboBoxDelegate::addItem(const string& text, const QVariant& value){
	m_items[value.toUInt()] = text;
}

void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
								const QModelIndex &index) const
{
	uint32 value = index.data().toUInt();
	QStyleOptionViewItemV4 myOption = option;
	QString text = LOCAL8BITSTR(undefineStr);
	QMap<uint32, string>::const_iterator it = m_items.find(value);
	if(m_items.end() != it)
		text = LOCAL8BITSTR(it.value().c_str());
	myOption.text = text;
	//myOption.font.setBold(true);
	QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
//	QApplication::style()->drawItemText(painter, option.rect, Qt::AlignLeft | Qt::AlignVCenter,
//																	option.palette, true, text);
}
