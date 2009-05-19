#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QWidget>
#include "ui_ItemEditor.h"
class QAbstractItemModel;
class QAbstractItemDelegate;

class ItemEditor : public QWidget
{
	Q_OBJECT
public:

	enum ItemEditorMode {
		InitMode,
		EditMode,
		DisplayMode
	};

	ItemEditor(QWidget *parent = 0);
	~ItemEditor();
	void clearData();
	void changeMode(ItemEditorMode mode);

protected:
	QAbstractItemModel* m_DataModel;
	void setTitle(QString& title);
	void addData(int row, int column, const QVariant& data);
	void setHeaderData(int column, const QVariant& data);
	void hideColumn(int column);
	void setDelegate(int column, QAbstractItemDelegate* delegate);
	void appendColumn(int column);
	virtual void* getData() = 0;

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
