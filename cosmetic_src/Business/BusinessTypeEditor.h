#ifndef BUSINESSTYPEEDITOR_H
#define BUSINESSTYPEEDITOR_H

#include "ItemEditor.h"

class BusinessTypeEditor : public ItemEditor
{
public:
	BusinessTypeEditor(QWidget *parent);
	~BusinessTypeEditor();
	virtual void* getData();

private:
	
};

#endif // BUSINESSTYPEEDITOR_H
