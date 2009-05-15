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
	~Staff();
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
/*
	friend bool operator==(Staff x, Staff y){
		return (	y.id() == x.id() &&
				y.level()== x.level() &&
				y.name() == x.name() &&
				y.password() ==x.password() &&
				y.type() == x.type() &&
				y.sex() == x.sex() &&
				y.address() == x.address() &&
				y.cell() == x.cell() &&
				y.phone() == x.phone() &&
				y.status() == x.status() &&
				y.rating() == x.rating() &&
				y.description() == x.description() &&
				y.bonus() == x.bonus()
				);
	}
*/	/*
	inline bool operator==(Staff x){
		return (	m_id == x.id() &&
				m_level == x.level() &&
				m_name == x.name() &&
				m_password ==x.password() &&
				m_type == x.type() &&
				m_sex == x.sex() &&
				m_address == x.address() &&
				m_cell == x.cell() &&
				m_phone == x.phone() &&
				m_status == x.status() &&
				m_rating == x.rating() &&
				m_description == x.description() &&
				m_bonus == x.bonus()
				);
	}
*/
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
