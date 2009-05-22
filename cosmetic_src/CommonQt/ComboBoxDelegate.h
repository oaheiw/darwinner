///////////////////////////////////////////////////////////
//  ComboBoxDelegate.h
//  Implementation of the Class ComboBoxDelegate
//  Created on:      22-ÎåÔÂ-2009 12:07:58
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_19BE22B5_3A30_4ebd_ABC8_26FF8BF060CE__INCLUDED_)
#define EA_19BE22B5_3A30_4ebd_ABC8_26FF8BF060CE__INCLUDED_

#include <string>
#include <QMap>
using namespace std;

#include <QItemDelegate>
#include "common.h"
class QModelIndex;
class QWidget;
class QVariant;

class ComboBoxDelegate : public QItemDelegate
{

public:
	ComboBoxDelegate(QObject *parent = 0);
	virtual ~ComboBoxDelegate();
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void addItem(const string& text, const QVariant& value);

private:
	QMap<uint32, string> m_items;

};
#endif // !defined(EA_19BE22B5_3A30_4ebd_ABC8_26FF8BF060CE__INCLUDED_)
