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

	uint32 getConsumeTime();
	uint64 getDeposit();
	uint32 getLevel();
	uint64 getTotalConsume();
	void setConsumeTime(uint32 newVal);
	void setDeposit(uint64 newVal);
	void setLevel(uint32 newVal);
	void setTotalConsume(uint64 newVal);

	inline bool operator==(Customer &x){
		return (	dynamic_cast<const Human&>(x) == dynamic_cast<const Human&>(*this) &&
			m_level == x.getLevel() &&
			m_consumeTime == x.getConsumeTime() &&
			m_deposit == x.getDeposit() &&
			m_totalConsume == x.getTotalConsume()
			);
	}

	class CustomerIdMatcher {
	public:
		CustomerIdMatcher(uint32 id):m_val(id) { }
		inline bool operator()(Customer &x) 
		{
			return 0 == x.id() || x.id() == m_val;
		}
	private:
		uint32 m_val;
	};

private:
	uint32 m_consumeTime;
	uint64 m_deposit;
	uint32 m_level;
	uint64 m_totalConsume;

};

#endif //!defined(EA_E5BCEF46_EE15_4d64_A28B_54943A821136__INCLUDED_)