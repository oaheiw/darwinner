#ifndef BUSINESSTYPEEDITOR_H
#define BUSINESSTYPEEDITOR_H

#include "ItemEditor.h"
class BusinessType;
#include <list>
using namespace std;

class BusinessTypeEditor : public ItemEditor
{
public:
	BusinessTypeEditor(QWidget *parent);
	virtual ~BusinessTypeEditor();
	virtual void* getData();
	void addBusinessType(const BusinessType& data);
	void addBusinessType(const list<BusinessType>* data);
};

#endif // BUSINESSTYPEEDITOR_H
