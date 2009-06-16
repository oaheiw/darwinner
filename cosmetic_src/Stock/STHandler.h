///////////////////////////////////////////////////////////
//  STHandler.h
//  Implementation of the Class STHandler
//  Created on:      15-ÁùÔÂ-2009 18:01:05
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_B5FA0C50_6F9A_4fd3_8F88_B092F8EB735C__INCLUDED_)
#define EA_B5FA0C50_6F9A_4fd3_8F88_B092F8EB735C__INCLUDED_

#include "IEventObserver.h"
#include "DUIHandler.h"
#include "Stock.h"
#include "Business.h"
#include "Inventory.h"
#include <list>
class Message;

class STHandler : public DUIHandler, public IEventObserver
{

public:
	STHandler();
	~STHandler();
	virtual void OnEvent(Message& ev);
	virtual void StartAction(Message& act);

protected:
	virtual bool CheckRight(uint32 actionId);

private:
	DUIObserver* m_mainWindow;
	list<Business> m_commodityCache;
	list<Stock> m_stockCache;
	list<Inventory> m_inventoryCache;

};
#endif // !defined(EA_B5FA0C50_6F9A_4fd3_8F88_B092F8EB735C__INCLUDED_)
