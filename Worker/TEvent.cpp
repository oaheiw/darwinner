#include "common.h"
#include "TEvent.h"

TEvent::TEvent(QEvent::Type type)
	: QEvent(type)
{
	m_data = NULL;
}

TEvent::TEvent(QEvent::Type type, Message* data)
	: QEvent(type)
{
	m_data = data;
}

TEvent::~TEvent()
{
	if(NULL != m_data)
		delete m_data;
}

void TEvent::setData(Message* data)
{
	m_data = data;
}

Message* TEvent::data()
{
	return m_data;
}