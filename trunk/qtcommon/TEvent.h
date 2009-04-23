#ifndef TEVENT_H
#define TEVENT_H

#include <QEvent>
class Message;

class TEvent : public QEvent
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
