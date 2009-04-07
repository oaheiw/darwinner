#ifndef COMMON_H
#define COMMON_H

#define D_DEMO
#include <Qt/qglobal.h>
typedef unsigned int uint32;
typedef unsigned char byte;

#define DLL_EXPORT  __declspec (dllexport)
#define NULL 0
#define MESSAGE_BUFFER_SIZE (4096)
#define ID_MAX_LEN (16)
#define PW_MAX_LEN (16)
#define STUFFNAME_MAX_LEN (32)
#define DESCRP_MAX_LEN (2048-128)

enum MESSAGE_TYPE {
	ACTION = 1,
	RESPONSE = 100,
	EVENT = 200
};

enum ACTION{
	ACTION_LOGIN = ACTION + 1,
	ACTION_LOGOFF,
	ACTION_EXIT,
	ACTION_MAINMENU,
	ACTION_STUFFMGNT,
	ACTION_END
};

enum EVENT{
	EVENT_LOGGEDIN = EVENT + 1,
	EVENT_LOGGEDOFF,
	EVENT_EXIT,
	EVENT_MAINMENU,
	EVENT_STUFFMGNT,
	EVENT_END
};

enum TYPE {
	TYPE_BOSS = 0,
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

namespace WorkerEventType {
	const int Db = 2000;
	const int Net = 3000;
}


#endif
