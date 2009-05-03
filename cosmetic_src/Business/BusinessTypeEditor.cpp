#include "BusinessTypeEditor.h"
#include "common.h"
#include "BusinessType.h"
#include <list>
using namespace std;

BusinessTypeEditor::BusinessTypeEditor(QWidget *parent)
: ItemEditor(parent)
{
	appendColumn(4);
	int col = 0;
	setHeaderData(col++, LOCAL8BITSTR("±‡∫≈"));
	setHeaderData(col++, LOCAL8BITSTR("√˚≥∆"));
	setHeaderData(col++, LOCAL8BITSTR(" Ù–‘"));
	setHeaderData(col++, LOCAL8BITSTR("√Ë ˆ"));

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
		temp.setName(m_DataModel->index(row, col++).data().toString().toLocal8Bit().data());
		if(temp.getName().empty()) continue;// ignore item with empty name
		temp.setCategory(m_DataModel->index(row, col++).data().toUInt());
		temp.setDescription(m_DataModel->index(row, col++).data().toString().toLocal8Bit().data());
		data->push_back(temp);
	}
	return data;
}

