///////////////////////////////////////////////////////////
//  ProgressBarDelegate.cpp
//  Implementation of the Class ProgressBarDelegate
//  Created on:      05-ÎåÔÂ-2009 18:53:16
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "ProgressBarDelegate.h"
#include <QProgressBar>
#include <QApplication>
#include <QSlider>
#include "UiStrings.h"


ProgressBarDelegate::ProgressBarDelegate(QObject *parent)
:QItemDelegate(parent)	, m_format("%p")
{
	
}

QWidget *ProgressBarDelegate::createEditor
(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
	QSlider* editor = new QSlider(parent);
	editor->setRange(m_min, m_max);
	return editor;
}

void ProgressBarDelegate::setEditorData
(QWidget *editor, const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();
	QSlider *slider = static_cast<QSlider*>(editor);
	slider->setValue(value);
}

void ProgressBarDelegate::setModelData
(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QSlider *slider = static_cast<QSlider*>(editor);
	int value = slider->value();
	model->setData(index, value, Qt::EditRole);
}

void ProgressBarDelegate::updateEditorGeometry
(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
	editor->setGeometry(option.rect);
}

void ProgressBarDelegate::setFormat(QString& newVal){

	m_format = newVal;
}

void ProgressBarDelegate::setRange(uint32 min, uint32 max)
{
	m_min = min;
	m_max = max;
}

void ProgressBarDelegate::paint
(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
	int h = ((double)progress/(double)progressBarOption.maximum)*COLOR_GREEN;
	progressBarOption.palette.setColor(QPalette::Normal, QPalette::Highlight, 
										QColor::fromHsv(h, 255, 255));
	QApplication::style()->drawControl
		(QStyle::CE_ProgressBar, &progressBarOption, painter);
}


