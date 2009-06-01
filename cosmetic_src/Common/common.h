///////////////////////////////////////////////////////////
//  common.h
//  Implementation of the common
//  Created on:      08-Apr-2009 10:06:32 AM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#ifndef EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_
#define EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_

#include <string>
#include <map>
using namespace std;

typedef unsigned int uint32;
typedef int int32;
typedef unsigned char byte;
typedef long long int64;
typedef unsigned long long uint64;

typedef map<uint32, string> ArrayUint32String;
typedef map<string, string> ArrayStringString;


#ifndef NULL
#define NULL 0
#endif

#define _CONSOLE_DEBUG

#ifdef _CONSOLE_DEBUG
#include <iostream>
#include <iomanip>
#define DBHEX(info, para)\
		{\
		std::cout<<__FILE__<<":"<<std::dec<<__LINE__<<" "<<info<<" "\
			<<std::hex<<para<<std::endl;\
		}
#define DBDEC(info, para)\
		{\
			std::cout<<__FILE__<<":"<<std::dec<<__LINE__<<" "<<info<<" "\
			<<para<<std::endl;\
		}

#else
#define DBHEX(info, para)
#define DBDEC(info, para)
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
#define ID_MAX_LEN (16)
#define PW_MAX_LEN (16)
#define NAME_MAX_LEN (32)
#define PHONE_MAX_LEN (16)
#define PIC_MAX_SIZE (1.5)
#define ACTION_FLAG (0x00000080)
#define EVENT_FLAG (0x00000000)

#define SUPERUSERID 10000

#define  DBCONNECTION_COMMON "COMMONDB"
#define  DBCONNECTION_SM "SMDB"
#define  DBCONNECTION_BM "BMDB"
#define  DBCONNECTION_CM "CMDB"

#define STAFFLEVEL "stafflevel"
#define STAFFTYPE "stafftype"
#define STAFFSTATE "staffstate"
#define BUSINESSTYPE "businesstype"
#define SEXNAMES "sexnames"
#define BUSINESSCATEGORE "businesscategore"
#define CUSTOMERLEVEL "customerlevel"

#define STYLE_WIN98 "windows"
#define STYLE_WINXP "windowsxp"
#define STYLE_WINVISTA "windowsvista"
#define STYLE_MOTIF "motif"
#define STYLE_CDE "cde"
#define STYLE_PLASTIQUE "plastique"
#define STYLE_CLEAN "cleanlooks"

#define COLOR_GREEN (110)

#define DIR_SEPERATOR "/"

enum SEX {
	SEX_UNDEFINE = 0,
    SEX_MALE,
    SEX_FEMALE,
    SEX_END
};

enum BUSINESS_CATEGORY
{
	BC_MEMEBERDEPOSIT = 0,
	BC_MEMEBERCARD,
	BC_SERVICE,
	BC_SALE,
	BC_SPENDING,
	BC_SALARY,
	BC_STOCK,
	BC_RETURNSTOCK,
	BC_END
};


//GROUP should be less than 127
enum GROUP {
	GROUP_COMMON = 0,
	GROUP_STAFFMGNT = 1,
	GROUP_BUSINESSMGNT = 2,
	GROUP_SHOPMGNT = 3,
	GROUP_CUSTOMERMGNT = 4,
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

//SUBGROUP should be less than 255
enum SUBGROUP_CM {
	SUBGROUP_CM_BROWSE = 1,
	SUBGROUP_CM_INFOMGNT, // 2
	SUBGROUP_CM_RECORDMGNT, // 3
	SUBGROUP_CM_ADVANCEDMGNT, // 4
	SUBGROUP_CM_END
};

enum ERROR {
	ERROR_NO_ERROR = 0,
	ERROR_DBERROR = -1,
	ERROR_PASSWORD_WRONG = -2,
	ERROR_REMOVE = -3,
	ERROR_END
};

#endif

