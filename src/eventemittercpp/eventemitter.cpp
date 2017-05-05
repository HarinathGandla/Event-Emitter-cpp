#include "eventemitter.h"

#include <algorithm>

namespace event
{
    
void EventEmitter::removeHandler(int handlerId)
{
    std::lock_guard<std::mutex> lock( handlerMapMutex_);

    auto it = std::find_if( handlerMap_.begin(), handlerMap_.end(), [handlerId]( const HandlerMap::value_type& handlerItem)
    {
        return handlerItem.second->connectionId == handlerId;
    });
    
    if( it != handlerMap_.end())
        handlerMap_.erase( it);
}

EventEmitter::~EventEmitter()
{}

    
}
