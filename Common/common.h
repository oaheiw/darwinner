///////////////////////////////////////////////////////////
//  common.h
//  Implementation of the common
//  Created on:      08-Apr-2009 10:06:32 AM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#ifndef EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_
#define EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_

#ifdef _CONSOLE_DEBUG
#include <iostream>
using namespace std;
#define DBINFO(info) std::cout<<info<<endl;
#else
#define DBINFO(info) {}
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
  
//#define DLL_EXPORT  __declspec (dllexport)
#define DLL_EXPORT 

#define MESSAGE_BUFFER_SIZE (4096)
#define ID_MAX_LEN (16)
#define PW_MAX_LEN (16)
#define STUFFNAME_MAX_LEN (32)
#define DESCRP_MAX_LEN (2048-128)
#define DBFILE "./cosmeticdb"
#define SQLITEMARK "SQLite format 3"
#define SQLITEMARKLEN (15)

enum SINFO {
	SINFO_BROWSE = 0,
	SINFO_MODIFY,
	SINFO_NEW
};

#endif
