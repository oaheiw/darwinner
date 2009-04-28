///////////////////////////////////////////////////////////
//  Singleton.h
//  Implementation of the Class Singleton
//  Created on:      02-Apr-2009 21:26:26
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#if !defined(EA_7651E40F_B1AE_46ba_BB3B_F8AE8EFBF7C8__INCLUDED_)
#define EA_7651E40F_B1AE_46ba_BB3B_F8AE8EFBF7C8__INCLUDED_

template<class T> class Singleton
{

public:
	~Singleton() {}
	inline static T* instance(){
		if (NULL == m_instance) {
			m_instance = new T();
		}
		return m_instance;
	}

protected:
	Singleton() {}

private:
	static T* m_instance;
};

template<class T> T* Singleton<T>::m_instance = NULL;
#endif // !defined(EA_7651E40F_B1AE_46ba_BB3B_F8AE8EFBF7C8__INCLUDED_)
