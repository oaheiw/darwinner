///////////////////////////////////////////////////////////
//  common.h
//  Implementation of the common
//  Created on:      08-Apr-2009 10:06:32 AM
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#ifndef EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_
#define EA_9F454DB8_A969_4830_9B7B_1DCC06D3333D6__INCLUDED_

#define D_DEMO

typedef unsigned int uint32;
typedef unsigned char byte;

#ifndef NULL
#define NULL 0
#endif


//#define DLL_EXPORT  __declspec (dllexport)
#define DLL_EXPORT 

#define MESSAGE_BUFFER_SIZE (4096)
#define ID_MAX_LEN (16)
#define PW_MAX_LEN (16)
#define STUFFNAME_MAX_LEN (32)
#define DESCRP_MAX_LEN (2048-128)

#define DBNAME "cosmeticdb"
#define CREATE_STAFF_TABLE "CREATE TABLE staff (id INTEGER PRIMARY KEY, password TEXT, name TEXT, jobId INTEGER REFERENCES jobTitle(id), levelId INTEGER REFERENCES level(id), sex CHAR DEFAULT '0', status CHAR DEFAULT '0', cell TEXT, phone TEXT, address TEXT, descrption TEXT)"
#define INSERTINTO_STAFF_TABLE "INSERT INTO staff (password, name, jobId, levelId, sex, status, cell, phone, address, descrption) " "VALUES (:password, :name, :jobId, :levelId, :sex, :status, :cell, :phone, :address, :descrption)"
#endif
