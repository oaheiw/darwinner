///////////////////////////////////////////////////////////
//  common.h
//  Implementation of the common
//  Created on:      08-Apr-2009 10:06:32 AM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#ifndef EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_
#define EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_

typedef unsigned int uint32;
typedef unsigned char byte;

#ifndef NULL
#define NULL 0
#endif

#define _CONSOLE_DEBUG

#ifdef _CONSOLE_DEBUG
#include <iostream>
#include <iomanip>
#define DBINFO(info, para)\
		{\
			std::cout<<__FILE__<<" Line:"<<std::dec<<__LINE__<<" "<<info<<" "<<std::hex<<para<<std::endl;\
		}
#else
#define DBINFO(info, para) {}
#endif

#define TOBE_REALIZIED MessageBox::showMessageBox(this, QMessageBox::Information, "实现中",  "该功能正在实现中……")

#define ASSERT_DEBUG
#ifdef ASSERT_DEBUG
#include <assert.h>
#define ASSERT_POINTER(p) assert( NULL != p)
#else
#define ASSERT_POINTER(p) if(NULL == p) return
#endif

#define F_OK (0)
#define W_OK (2)
#define R_OK (4)
#define RW_OK (6)
  
#define MB (1024*1024)
#define MESSAGE_BUFFER_SIZE (4096)
#define ID_MAX_LEN (16)
#define PW_MAX_LEN (16)
#define NAME_MAX_LEN (32)
#define PHONE_MAX_LEN (16)
#define PIC_MAX_SIZE (1.5)
#define ACTION_FLAG (0x80)
#define EVENT_FLAG (0x00)

#define DBCONNECTION_COMMON "COMMONDB"
#define DBCONNECTION_SM "SMDB"
#define DBCONNECTION_BM "BMDB"

enum SEX {
	SEX_UNDEFINE = 0,
    SEX_MALE,
    SEX_FEMALE,
    SEX_END
};

enum BusinessCategory
{
	BusinessCost = 0,
	BusinessService = 1,
	BusinessSale = 2,
	BusinessCategoryEnd
};


//GROUP should be less than 127
enum GROUP {
	GROUP_COMMON = 0,
	GROUP_STAFFMGNT = 1,
	GROUP_BUSINESSMGNT = 2,
	GROUP_SHOPMGNT = 3,
	GROUP_CLIENTMGNT = 4,
	GROUP_END
};

//SUBGROUP should be less than 255
enum SUBGROUP_SM {
	SUBGROUP_SM_STAFFBROWSE = 1,
	SUBGROUP_SM_INFOMGNT, // 2
	SUBGROUP_SM_SALARYMGNT, // 3
	SUBGROUP_SM_PASSWORDMGNT, // 4
	SUBGROUP_SM_ADVANCEDMGNT, // 5
	SUBGROUP_SM_END
};

//SUBGROUP should be less than 255
enum SUBGROUP_BM {
	SUBGROUP_BM_BROWSE = 1,
	SUBGROUP_BM_INFOMGNT, // 2
	SUBGROUP_BM_RECORDMGNT, // 3
	SUBGROUP_BM_ADVANCEDMGNT, // 4
	SUBGROUP_BM_END
};


enum ERROR {
	ERROR_NO_ERROR = 0,
	ERROR_DBERROR = -1,
	ERROR_PASSWORD_WRONG = -2,
	ERROR_END
};

static char* lastDir = "./";

#endif
