#include "BusinessTypeEditor.h"
#include "common.h"
#include "BusinessType.h"
#include <list>
#include "UiStrings.h"
#include "SpinBoxDelegate.h"
using namespace UiStr;
using namespace std;

BusinessTypeEditor::BusinessTypeEditor(QWidget *parent)
: ItemEditor(parent)
{
	appendColumn(4);
//	setTitle(LOCAL8BITSTR(bmTypeEditorStr));
	setTitle(LOCAL8BITSTR(""));
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeIdStr));
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeNameStr));
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeCategoryStr));
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeDescriptionStr));
}

BusinessTypeEditor::~BusinessTypeEditor()
{

}

void* BusinessTypeEditor::getData()
{
	list<BusinessType>* data = new list<BusinessType>;
	ASSERT_POINTER(m_DataModel);
	for (int row=0; row < m_DataModel->rowCount(); row++)
	{	
		BusinessType temp;
		int col=0;
		temp.setId(m_DataModel->index(row, col++).data().toUInt());
		temp.setName(string(m_DataModel->index(row, col++).data().toString().toLocal8Bit().data()));
		if(temp.getName().empty()) continue;// ignore item with empty name
		temp.setCategory(m_DataModel->index(row, col++).data().toUInt());
		temp.setDescription(string(m_DataModel->index(row, col++).data().toString().toLocal8Bit().data()));
		data->push_back(temp);
	}
	return data;
}

void BusinessTypeEditor::addBusinessType(const BusinessType & data)
{
	int col = 0;
	addData(0, col++, data.getId());
	addData(0, col++, LOCAL8BITSTR(data.getName().c_str()));
	addData(0, col++, LOCAL8BITSTR(BusinessCategoryStr[data.getCategory()]));
	addData(0, col++, LOCAL8BITSTR(data.getDescription().c_str()));
}
