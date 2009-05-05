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
typedef unsigned char byte;
typedef map<uint32, string> StringArray;

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
  
static const uint32 MB = 1024*1024;
static const uint32 ID_MAX_LEN = 16;
static const uint32 PW_MAX_LEN = 16;
static const uint32 NAME_MAX_LEN = 32;
static const uint32 PHONE_MAX_LEN = 16;
static const uint32 PIC_MAX_SIZE = 1.5;
static const uint32 ACTION_FLAG = 0x00000080;
static const uint32 EVENT_FLAG = 0x00000000;

static const char*  DBCONNECTION_COMMON = "COMMONDB";
static const char*  DBCONNECTION_SM = "SMDB";
static const char*  DBCONNECTION_BM = "BMDB";

static const char* STYLE_WIN98 = "windows";
static const char* STYLE_WINXP = "windowsxp";
static const char* STYLE_WINVISTA = "windowsvista";
static const char* STYLE_MOTIF = "motif";
static const char* STYLE_CDE = "cde";
static const char* STYLE_PLASTIQUE = "plastique";
static const char* STYLE_CLEAN = "cleanlooks";

static const char* DIR_SEPERATOR = "/";

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

#include "Singleton.h"

#endif
