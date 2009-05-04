#include "StaffListView.h"
#include <QSortFilterProxyModel>
#include "UiStrings.h"
using namespace UiStr;

StaffListView::StaffListView(QWidget *parent)
: ItemView(parent)
{

	QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
	setProxy(proxy);
	appendColumn(11);
	setTitle(LOCAL8BITSTR(staffBrowseStr));
	int col = 0;
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(staffIDStr));
	setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(staffNameStr));
	setColumnWidth(col, 50);
	setHeaderData(col++, LOCAL8BITSTR(staffSexStr));
	setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(staffJobStr));
	setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(staffLevelStr));
	setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(staffStatusStr));
	setColumnWidth(col, 80);
	setHeaderData(col++, LOCAL8BITSTR(staffRatingStr));
	setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(staffCellStr));
	setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(staffPhoneStr));
	setColumnWidth(col, 200);
	setHeaderData(col++, LOCAL8BITSTR(staffAddressStr));
	setColumnWidth(col, 200);
	setHeaderData(col++, LOCAL8BITSTR(staffDescriptionStr));

}

StaffListView::~StaffListView()
{

}

void addStaffs(list<Staff> data)
{	

}

