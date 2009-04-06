///////////////////////////////////////////////////////////
//  Singleton.h
//  Implementation of the Class Singleton
//  Created on:      02-四月-2009 21:26:26
//  Original author: Sunlight Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_7651E40F_B1AE_46ba_BB3B_F8AE8EFBF7C8__INCLUDED_)
#define EA_7651E40F_B1AE_46ba_BB3B_F8AE8EFBF7C8__INCLUDED_

///////////////////////////////////////////////////////////
//  Singleton.cpp
//  Implementation of the Class Singleton
//  Created on:      02-四月-2009 21:26:26
//  Original author: Sunlight Kuo
///////////////////////////////////////////////////////////
#include "common.h"

//#include "Singleton.h"
template<class T> class DLL_EXPORT Singleton
{

public:
	~Singleton();

	static T* instance();

protected:
	Singleton();

private:
	static T* m_instance;

};


template<class T> T* Singleton<T>::m_instance = 0;


template<class T> Singleton<T>::~Singleton(){

}

template<class T> Singleton<T>::Singleton(){

}


template<class T>  T* Singleton<T>::instance(){
	if (0 == m_instance) {
		m_instance = new T();
	}
	return m_instance;
}

#endif // !defined(EA_7651E40F_B1AE_46ba_BB3B_F8AE8EFBF7C8__INCLUDED_)
