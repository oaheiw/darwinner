///////////////////////////////////////////////////////////
//  Customer.h
//  Implementation of the Class Customer
//  Created on:      24-ÎåÔÂ-2009 17:15:39
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_E5BCEF46_EE15_4d64_A28B_54943A821136__INCLUDED_)
#define EA_E5BCEF46_EE15_4d64_A28B_54943A821136__INCLUDED_

#include "common.h"
#include "Human.h"

class Customer : public Human
{

public:
	Customer();
	virtual ~Customer();

	uint32  consumeTime();
	uint32  deposit();
	uint32  level();
	void setconsumeTime(uint32 newVal);
	void setdeposit(uint32 newVal);
	void setlevel(uint32 newVal);

private:
	uint32 m_consumeTime;
	uint64 m_deposit;
	uint32 m_level;

};
#endif // !defined(EA_E5BCEF46_EE15_4d64_A28B_54943A821136__INCLUDED_)
