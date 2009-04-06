#include "common.h"
#include "TEvent.h"

TEvent::TEvent(QEvent::Type type)
	: QEvent(type)
{
	m_data = NULL;
}

TEvent::~TEvent()
{

}

void TEvent::setData(Message* data)
{
	m_data = data;
}

Message* TEvent::data()
{
	return m_data;
}