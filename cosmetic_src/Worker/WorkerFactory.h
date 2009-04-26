///////////////////////////////////////////////////////////
//  ProcesserFactory.h
//  Implementation of the Class ProcesserFactory
//  Created on:      03-Apr-2009 15:42:32
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_13647169_8ED3_4854_A156_A8B94B816E97__INCLUDED_)
#define EA_13647169_8ED3_4854_A156_A8B94B816E97__INCLUDED_
#include "IActionHandler.h"

class WorkerFactory
{

public:
	WorkerFactory();
	~WorkerFactory();

	IActionHandler* CreateWorker();

private:
	IActionHandler* m_handler;

};
#endif // !defined(EA_13647169_8ED3_4854_A156_A8B94B816E97__INCLUDED_)
