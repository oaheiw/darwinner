#ifndef STAFFLISTVIEW_H
#define STAFFLISTVIEW_H

#include "ItemView.h"
#include "common.h"
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
	ArrayUint32String* m_LevelNames;
	ArrayUint32String* m_TypeNames;
	ArrayUint32String* m_StateNames;
};

#endif // STAFFLISTVIEW_H
