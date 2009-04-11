///////////////////////////////////////////////////////////
//  messagedef.h
//  Implementation of the messagedef
//  Created on:      08-Apr-2009 10:06:32 AM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_9F454DB8_A969_4830_9B7B_1DCC06DF5CD6__INCLUDED_)
#define EA_9F454DB8_A969_4830_9B7B_1DCC06DF5CD6__INCLUDED_

#define EventDb (2000)
#define EventNet (3000)
#define EventLocal (4000)


enum MESSAGE_TYPE {
	ACTION = 0,
	RESPONSE = 100,
	EVENT = 200
};

enum ACTION{
	ACTION_SYSTEM_START = ACTION + 1,
	ACTION_LOGIN,
	ACTION_LOGOFF,
	ACTION_EXIT,
	ACTION_MAINMENU,
	ACTION_STAFFMGNT,
	ACTION_GETSTAFF,
	ACTION_END
};

enum EVENT{
	EVENT_SYSTEM_START = EVENT +1,
	EVENT_LOGGEDIN,
	EVENT_LOGGEDOFF,
	EVENT_EXIT,
	EVENT_MAINMENU,
	EVENT_STAFFMGNT,
	EVENT_STAFFS,
	EVENT_END
};

enum TYPE {
	TYPE_SUPPER = 0,
	TYPE_BOSS,
	TYPE_SHOP_MANAGER,
	TYPE_CASHER,
	TYPE_BARBER,
	TYPE_WASHER,
	TYPE_BEAUTICIAN,
	TYPE_MASSAGER
};

enum LEVEL {
	LEVEL_ROOKIE = 0,
	LEVEL_EXPERIENCED,
	LEVEL_SKILLED,
	LEVEL_ADVANCED,
	LEVEL_MASTER
};

enum SEX {
	SEX_UNDEFINED = 0,
	SEX_MALE,
	SEX_FEMALE
};


#endif // !defined(EA_9F454DB8_A969_4830_9B7B_1DCC06DF5CD6__INCLUDED_)
