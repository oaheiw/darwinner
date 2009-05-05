#ifndef BUSINESSTYPEEDITOR_H
#define BUSINESSTYPEEDITOR_H

#include "ItemEditor.h"
class BusinessType;

class BusinessTypeEditor : public ItemEditor
{
public:
	BusinessTypeEditor(QWidget *parent);
	~BusinessTypeEditor();
	virtual void* getData();
	void addBusinessType(const BusinessType& data);
	
};

#endif // BUSINESSTYPEEDITOR_H
