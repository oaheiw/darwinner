///////////////////////////////////////////////////////////
//  ProgressBarDelegate.cpp
//  Implementation of the Class ProgressBarDelegate
//  Created on:      05-ÎåÔÂ-2009 18:53:16
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "ProgressBarDelegate.h"
#include <QProgressBar>
#include <QApplication>
#include "UiStrings.h"


ProgressBarDelegate::ProgressBarDelegate(QObject *parent)
:QItemDelegate(parent)	, m_format("%p")
{
	
}

QWidget *ProgressBarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
	QProgressBar* editor = new QProgressBar(parent);
	editor->setFormat(m_format);
	editor->setAlignment(Qt::AlignCenter);
	return editor;
}

void ProgressBarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();
	QProgressBar *progressBar = static_cast<QProgressBar*>(editor);
	progressBar->setValue(value);
}

void ProgressBarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QProgressBar *progressBar = static_cast<QProgressBar*>(editor);
	int value = progressBar->value();
	model->setData(index, value, Qt::EditRole);
}

void ProgressBarDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void ProgressBarDelegate::setFormat(QString& newVal){

	m_format = newVal;
}

void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
						   const QModelIndex &index) const
{
	int progress = index.data().toInt();

	QStyleOptionProgressBar progressBarOption;
	progressBarOption.rect = option.rect;
	progressBarOption.minimum = 0;
	progressBarOption.maximum = 100;
	progressBarOption.progress = progress;
	progressBarOption.text = QString::number(progress) + LOCAL8BITSTR(scoreStr);
	progressBarOption.textAlignment = Qt::AlignCenter;
	progressBarOption.textVisible = true;

	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
}


