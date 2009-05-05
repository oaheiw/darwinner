#ifndef STAFFLISTVIEW_H
#define STAFFLISTVIEW_H

#include "ItemView.h"
class QSortFilterProxyModel;
class Staff;
using namespace std;

class StaffListView : public ItemView
{
//	Q_OBJECT

public:
	StaffListView(QWidget *parent);
	~StaffListView();
	void addStaff(Staff& data);

private:
	
};

#endif // STAFFLISTVIEW_H
