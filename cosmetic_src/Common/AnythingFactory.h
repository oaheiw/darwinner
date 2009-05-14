///////////////////////////////////////////////////////////
//  AnythingFactory.h
//  Implementation of the Class AnythingFactory
//  Created on:      14-ÎåÔÂ-2009 11:52:50
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_2171E09C_8068_4294_A894_FA9F4A1B89E2__INCLUDED_)
#define EA_2171E09C_8068_4294_A894_FA9F4A1B89E2__INCLUDED_

/**
 * This is the class for create any object by designate the object name
 */
 #include <string>
 #include <map>
 using namespace std;
 
template<class T> class AnythingFactory
{

public:
	AnythingFactory()
	{
		m_anythingContainer.clear();
	}

	~AnythingFactory()
	{
		for(map<string, T*>::iterator it = m_anythingContainer.begin() ; 
		m_anythingContainer.end() != it ; it++) {
			T* anythingToDelete = it->second;
			delete anythingToDelete;
		}
		m_anythingContainer.clear();
	}

	static inline AnythingFactory<T>* instance() 
	{
		return &m_instance;
	}

	inline T* createAnything(string name)
	{
		if(m_anythingContainer.end() == m_anythingContainer.find(name)) {
			T* newAnything = new T();
			m_anythingContainer[name] = newAnything;
		}
		return m_anythingContainer[name];
	}

	inline bool deleteAnything(string name)
	{
		map<string, T*>::iterator it = m_anythingContainer.find(name);
			
		if(m_anythingContainer.end() != it) {
			T* anythingToDelete = it->second;
			delete anythingToDelete;
			m_anythingContainer.erase(it);
			return true;
		} else {
			return false;
		}
	}

private:
	static AnythingFactory<T> m_instance;
	map<string, T*> m_anythingContainer;

};

template<class T> AnythingFactory<T> AnythingFactory<T>::m_instance;

#endif // !defined(EA_2171E09C_8068_4294_A894_FA9F4A1B89E2__INCLUDED_)
