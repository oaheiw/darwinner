#ifndef STAFFLISTVIEW_H
#define STAFFLISTVIEW_H

#include "ItemView.h"
class QSortFilterProxyModel;

class StaffListView : public ItemView
{
//	Q_OBJECT

public:
	StaffListView(QWidget *parent);
	~StaffListView();
	void init(int col, QSortFilterProxyModel* proxy = NULL);

private:
	
};

#endif // STAFFLISTVIEW_H
