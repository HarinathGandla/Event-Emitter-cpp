#ifndef EVENT_EVENTSUBSCRIBER_H
#define EVENT_EVENTSUBSCRIBER_H

#include "connection.h"
#include "eventemitter.h"

namespace event 
{

class EventSubscriber
{
public:
    virtual ~EventSubscriber();
    
    template <typename Callback>
    void on( EventEmitter& emitter, int event, const Callback& callback);
        
private:
    ConnectionList list_;
};

template <typename Callback>
void EventSubscriber::on( EventEmitter& emitter, int event, const Callback& callback)
{
    list_.push_back( emitter.on( event, callback));
}

}

#endif // EVENT_EVENTSUBSCRIBER_H
