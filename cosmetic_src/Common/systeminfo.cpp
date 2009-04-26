#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "systeminfo.h"

void systeminfo::ToHex(const unsigned char * szOrigin, int nSize, char * szHex)
{
	char szTemp[10];
	int nIndex = 0;
		for(nIndex = 0; nIndex < nSize; nIndex ++)
		{
			sprintf(szTemp, "%02X", szOrigin[nIndex]);
			 if(nIndex == 0)
			 {
				strcpy(szHex, szTemp);
			 }
			 else
			 {
				strcat(szHex, szTemp);
			 }
		}
}

unsigned char* systeminfo::getCPUID()
{
	char szCPUDesc[13];
	char szCPUSNHex[25];
	char szCPUID[37];
	unsigned char szCPUSN[12];

	memset(szCPUDesc, 0, 13);
	memset(szCPUSNHex, 0, 25);
	memset(szCPUID, 0, 37);
	memset(szCPUSN, 0, 12);

	unsigned long ulEAX = 0U, ulEBX = 0U, ulECX = 0U, ulEDX = 0U;

//	__try
//	{
		_asm
	 {
		mov eax, 1
		cpuid
		mov ulEDX, edx
		mov ulEAX, eax
	}

 //检查是否有CPU序列号
 //注意，Intel文档中说检测edx的第18位是从第0位开始计算的
	 if(!(ulEDX & (1 << 18)))
	  return 0;
	 //获取序列号的后两个WORD
	 memcpy(&szCPUSN[8], &ulEAX, 4);

	 _asm
	 {
	  mov eax, 3
	  cpuid
	  mov ulECX, ecx
	  mov ulEDX, edx
	 }
	 //获取序列号的前4个WORD
	 memcpy(&szCPUSN[0], &ulECX, 4);
	 memcpy(&szCPUSN[4], &ulEDX, 4);

	 //获取CPU OEM信息
	 _asm
	 {
	  mov eax, 0
			   cpuid
			   mov dword ptr szCPUDesc[0], ebx
			   mov dword ptr szCPUDesc[4], edx
			   mov dword ptr szCPUDesc[8], ecx
	 }
//}
	ToHex(szCPUSN, 12, szCPUSNHex);
	sprintf(szCPUID, "%s%s", szCPUDesc, szCPUSNHex);

	return szCPUSN;
}
