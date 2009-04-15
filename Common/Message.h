///////////////////////////////////////////////////////////
//  Message.h
//  Implementation of the Class Message
//  Created on:      02-Apr-2009 18:03:38
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_DFF946BC_B0FA_4688_A3B1_8556052D1F43__INCLUDED_)
#define EA_DFF946BC_B0FA_4688_A3B1_8556052D1F43__INCLUDED_

#include "common.h"
#include <string>
using namespace std;

class Message
{

public:
	Message();
	Message(void* data);
	Message(uint32 type, void* data = 0);
	/*
	Message(const Message&);  
	Message &operator = (const Message&);   
	*/
	~Message();
	void* data();
	uint32 length();
	void setData(void* data, uint32 size);
	void setData(void* data);
	void setLength(uint32 length);
	void setType(uint32 type);
	uint32 type();

private:
	void* m_data;
	uint32 m_length;
	uint32 m_type;
	uint32 m_id;

};
#endif // !defined(EA_DFF946BC_B0FA_4688_A3B1_8556052D1F43__INCLUDED_)
