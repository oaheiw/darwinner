#include "BusinessTypeEditor.h"
#include "common.h"
#include "BusinessType.h"
#include <list>
#include "UiStrings.h"
#include "ComboBoxDelegate.h"
#include "AnythingFactory.h"
using namespace std;

BusinessTypeEditor::BusinessTypeEditor(QWidget *parent)
: ItemEditor(parent)
{
	appendColumn(4);
	setWindowTitle(LOCAL8BITSTR(bmTypeEditorStr));
	setTitle(LOCAL8BITSTR(""));
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeIdStr));
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeNameStr));
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeCategoryStr));
	setHeaderData(col++, LOCAL8BITSTR(bmBusinessTypeDescriptionStr));

	m_categoryNames = AnythingFactory<ArrayUint32String>::instance()->createAnything(BUSINESSCATEGORE);

	ComboBoxDelegate *delegate = new ComboBoxDelegate(this);
	for(ArrayUint32String::const_iterator it = m_categoryNames->begin() ; 
		m_categoryNames->end() != it ; it++) {
			if(it->first < BC_SPENDING) {
				delegate->addItem(it->second, it->first);
			}
	}
	setDelegate(2, delegate);
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
	addData(0, col++, data.getCategory());
	addData(0, col++, LOCAL8BITSTR(data.getDescription().c_str()));
}

void BusinessTypeEditor::addBusinessType(const list<BusinessType>* data)
{
	for(list<BusinessType>::const_iterator it = data->begin() ; 
		data->end() != it ; it++ )
			addBusinessType(*it);
}