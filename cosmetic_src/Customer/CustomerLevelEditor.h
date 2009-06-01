///////////////////////////////////////////////////////////
//  CustomerLevelEditor.h
//  Implementation of the Class CustomerLevelEditor
//  Created on:      31-ÎåÔÂ-2009 22:04:57
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_0857DF94_2AE5_4dc8_8D1B_A058BE8CDC4F__INCLUDED_)
#define EA_0857DF94_2AE5_4dc8_8D1B_A058BE8CDC4F__INCLUDED_

#include "ItemEditor.h"
class CustomerLevel;
class SpinBoxDelegate;
#include <list>
using namespace std;

class CustomerLevelEditor : public ItemEditor
{

public:
	CustomerLevelEditor(QWidget *parent = 0);
	virtual ~CustomerLevelEditor();
	void addCustomerLevel(const CustomerLevel& data);
	void addCustomerLevel(const list<CustomerLevel>* data);

protected:
	virtual void* getData();

private:
	SpinBoxDelegate* m_discountDelegate;
	SpinBoxDelegate* m_requireDelegate;
};
#endif // !defined(EA_0857DF94_2AE5_4dc8_8D1B_A058BE8CDC4F__INCLUDED_)
