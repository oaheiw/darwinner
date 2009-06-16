#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QItemDelegate>
#include "common.h"
#include "UiStrings.h"
class QModelIndex;

class SpinBoxDelegate : public QItemDelegate
{
public:
	SpinBoxDelegate(QObject *parent = 0);
	virtual ~SpinBoxDelegate() {};

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setRange(int32 min, int32 max);
	void setPrefix(const string& newVal);
	void setSuffix(const string& newVal);
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

private:
	int32 m_max;
	int32 m_min;
	string m_prefix;
	string m_suffix;
};

#endif
