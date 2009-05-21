///////////////////////////////////////////////////////////
//  ProgressBarDelegate.h
//  Implementation of the Class ProgressBarDelegate
//  Created on:      05-ÎåÔÂ-2009 18:53:16
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_611665E4_3806_4da3_86A1_33995CDF4EXX__INCLUDED_)
#define EA_611665E4_3806_4da3_86A1_33995CDF4EXX__INCLUDED_

#include <QItemDelegate>
#include "common.h"
class QModelIndex;


class ProgressBarDelegate : public QItemDelegate
{
public:

	ProgressBarDelegate(QObject* parent = 0);
	virtual ~ProgressBarDelegate(){

	}
	QWidget * createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void setEditorData(QWidget* editor, const QModelIndex& index) const;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void setFormat(QString& newVal);
	void setRange(uint32 min, uint32 max);
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
						   const QModelIndex &index) const;
	
private:
	QString m_format;
	uint32 m_min;
	uint32 m_max;
};
#endif // !defined(EA_611665E4_3806_4da3_86A1_33995CDF4E4E__INCLUDED_)
