///////////////////////////////////////////////////////////
//  Staff.h
//  Implementation of the Class Staff
//  Created on:      03-Apr-2009 18:24:52
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_)
#define EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_

#include "common.h"
#include "Human.h"

class Staff : public Human
{

public:
	Staff();
	virtual ~Staff();
	const uint32&  bonus() const;
	const uint32&  level() const;
	const short&  rating() const;
	const uint32&  status() const;
	const uint32&  type() const;
	void setbonus(const uint32& newVal);
	void setlevel(const uint32& newVal);
	void setrating(const short& newVal);
	void setstatus(const uint32& newVal);
	void settype(const uint32& newVal);
	virtual void clear();

	inline bool operator==(const Staff &x){
		return (	dynamic_cast<const Human&>(x) == dynamic_cast<const Human&>(*this) &&
				m_level == x.level() &&
				m_type == x.type() &&
				m_status == x.status() &&
				m_rating == x.rating() &&
				m_bonus == x.bonus()
				);
	}

	class idMatcher {
	public:
		idMatcher(uint32 id):m_val(id) { }
		inline bool operator()(Staff &x) 
		{
			return 0 == x.id() || x.id() == m_val;
		}
	private:
		uint32 m_val;
	};
	
private:
	uint32 m_level;
	uint32 m_type;
	uint32 m_status;
	short m_rating;
	uint32 m_bonus;
};


#endif // !defined(EA_D930C676_5D00_4035_86CC_873B36ABF8DE__INCLUDED_)
