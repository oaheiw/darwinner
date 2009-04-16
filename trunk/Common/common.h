///////////////////////////////////////////////////////////
//  common.h
//  Implementation of the common
//  Created on:      08-Apr-2009 10:06:32 AM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#ifndef EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_
#define EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_

#define _CONSOLE_DEBUG

#ifdef _CONSOLE_DEBUG
#include <iostream>
#include <time.h>
#include <iomanip>
#define DBINFO(info, para)\
					{\
					std::cout<<__FILE__<<"@"<<std::dec<<__LINE__<<"@"<<__TIME__<<": "<<info<<" "<<std::hex<<para<<std::endl;\
					}
#else
#define DBINFO(info, para) {}
#endif

typedef unsigned int uint32;
typedef unsigned char byte;

#ifndef NULL
#define NULL 0
#endif

#define F_OK (0)
#define W_OK (2)
#define R_OK (4)
#define RW_OK (6)
  
#define MESSAGE_BUFFER_SIZE (4096)
#define ID_MAX_LEN (16)
#define PW_MAX_LEN (16)
#define STUFFNAME_MAX_LEN (32)
#define DESCRP_MAX_LEN (2048-128)
#define MESSAGE_FLAG (0x80)

//GROUP should be less than 127
enum GROUP {
	GROUP_COMMON = MESSAGE_FLAG,
	GROUP_STAFFMGNT = MESSAGE_FLAG | 1,
	GROUP_GOODSMGNT = MESSAGE_FLAG | 2,
	GROUP_SHOPMGNT = MESSAGE_FLAG | 3,
	GROUP_CLIENTMGNT = MESSAGE_FLAG | 4
};

//SUBGROUP should be less than 255
enum SUBGROUP_SF {
	SUBGROUP_SF_STAFFBROWSE = 1,
	SUBGROUP_SF_INFOMGNT, // 2
	SUBGROUP_SF_SALARYMGNT, // 3
	SUBGROUP_SF_PASSWORDMGNT // 4
};

enum SINFO {
	SINFO_BROWSE = 0,
	SINFO_MODIFY,
	SINFO_NEW
};

#endif
