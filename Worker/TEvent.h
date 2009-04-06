#ifndef TEVENT_H
#define TEVENT_H

#include <QEvent>
#include "worker_global.h"
class Message;

class WORKER_EXPORT TEvent : public QEvent
{
public:
	TEvent(QEvent::Type, Message* data);
	TEvent(QEvent::Type);
	~TEvent();
	void setData(Message* data);
	Message* data();

private:
	Message* m_data;
	
};

#endif // TEVENT_H
