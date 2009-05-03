#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QWidget>
#include "ui_ItemEditor.h"
class QAbstractItemModel;
class QAbstractItemDelegate;

class ItemEditor : public QWidget
{

	enum ItemEditorMode {
		InitMode,
		EditMode,
		DisplayMode
	};

	Q_OBJECT
public:
	ItemEditor(QWidget *parent = 0);
	~ItemEditor();
	void setTitle(QString& title);
	void addData(int row, int column, const QVariant& data);
	void setHeaderData(int column, const QVariant& data);
	void clearData();
	void hideColumn(int column);
	void setDelegate(int column, QAbstractItemDelegate* delegate);
	void appendColumn(int column);
	void setMode(ItemEditorMode mode);
	virtual void* getData() = 0;

protected:
	QAbstractItemModel* m_DataModel;

signals:
	void submitted(void* data);

private slots:
	void add();
	void remove();
	void submit();

private:
	int m_mode;
	int m_column;
	Ui::ItemEditorClass ui;
};

#endif // ITEMEDITOR_H
