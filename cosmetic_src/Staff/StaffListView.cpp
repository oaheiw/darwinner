#include "StaffListView.h"
#include <QSortFilterProxyModel>
#include "Staff.h"
#include "UiStrings.h"
#include "ProgressBarDelegate.h"
using namespace UiStr;

extern map<uint32, string> g_LevelNames;
extern map<uint32, string> g_TypeNames;
extern map<uint32, string> g_StateNames;

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
	setColumnWidth(col, 120);
	setHeaderData(col++, LOCAL8BITSTR(staffRatingStr));
	setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(staffCellStr));
	setColumnWidth(col, 100);
	setHeaderData(col++, LOCAL8BITSTR(staffPhoneStr));
	setColumnWidth(col, 200);
	setHeaderData(col++, LOCAL8BITSTR(staffAddressStr));
	setColumnWidth(col, 200);
	setHeaderData(col++, LOCAL8BITSTR(staffDescriptionStr));

	ProgressBarDelegate *delegateRating = new ProgressBarDelegate(this);
	delegateRating->setFormat(LOCAL8BITSTR("%v/%m"));
	setDelegate(6, delegateRating);
}

StaffListView::~StaffListView()
{

}

void StaffListView::addStaff(Staff& data)
{	
	int col = 0;
	addData(0, col++, data.ID());
	addData(0, col++, LOCAL8BITSTR(data.Name().c_str()));
	addData(0, col++, LOCAL8BITSTR(sexStr[data.Sex()]));
	addData(0, col++, LOCAL8BITSTR(g_TypeNames[data.Type()].c_str()));
	addData(0, col++, LOCAL8BITSTR(g_LevelNames[data.Level()].c_str()));
	addData(0, col++, LOCAL8BITSTR(g_StateNames[data.status()].c_str()));
	addData(0, col++, data.getRating());
	addData(0, col++, LOCAL8BITSTR(data.cell().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.phone().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.address().c_str()));
	addData(0, col++, LOCAL8BITSTR(data.Descrp().c_str()));
}

