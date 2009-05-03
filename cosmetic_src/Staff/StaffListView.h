#ifndef STAFFLISTVIEW_H
#define STAFFLISTVIEW_H

#include "ItemView.h"
class QSortFilterProxyModel;
#include "Staff.h"
#include <list>
using namespace std;

class StaffListView : public ItemView
{
//	Q_OBJECT

public:
	StaffListView(QWidget *parent);
	~StaffListView();
	void addStaffs(list<Staff> data);

private:
	
};

#endif // STAFFLISTVIEW_H
