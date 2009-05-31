///////////////////////////////////////////////////////////
//  CustomerLevelEditor.h
//  Implementation of the Class CustomerLevelEditor
//  Created on:      31-ÎåÔÂ-2009 22:04:57
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_0857DF94_2AE5_4dc8_8D1B_A058BE8CDC4F__INCLUDED_)
#define EA_0857DF94_2AE5_4dc8_8D1B_A058BE8CDC4F__INCLUDED_

#include "ItemEditor.h"

class CustomerLevelEditor : public ItemEditor
{

public:
	CustomerLevelEditor();
	virtual ~CustomerLevelEditor();

protected:
	virtual void* getData();

};
#endif // !defined(EA_0857DF94_2AE5_4dc8_8D1B_A058BE8CDC4F__INCLUDED_)
