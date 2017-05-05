#ifndef EVENT_EVENTEMITTER_H
#define EVENT_EVENTEMITTER_H

#include <thread>
#include <map>
#include <mutex>
#include <list>
#include <atomic>
#include <iostream>
#include <type_traits>

#include "detail/handler.h"
#include "detail/functiontraits.h"
#include "connection.h"

namespace event 
{

class EventEmitter
{
public:
    template <typename ...Args>
    using Callback = std::function< void(const Args&...)>;
    
public:
    virtual ~EventEmitter();
    
    template <typename ...Args>
    ConnectionSharedPtr on(int eventId, Callback<Args...> callback);
    
    template <typename Func>
    ConnectionSharedPtr on(int eventId, Func callback);
    
    template <typename ...Args>
    void fire(int eventId, const Args&... args);
    
    void removeHandler( int handlerId);
    
private:
    using HandlerMap = std::multimap<int, detail::HandlerPtr>;
    HandlerMap handlerMap_;
    std::mutex handlerMapMutex_;
    
    std::atomic<int> connectionCounter_;
};

template <typename ...Args>
ConnectionSharedPtr EventEmitter::on(int eventId, EventEmitter::Callback<Args...> callback)
{
    std::lock_guard<std::mutex> lock( handlerMapMutex_);
    
    auto connectionId = connectionCounter_++;
    auto connection = ConnectionSharedPtr( new Connection( *this, connectionId));
    auto handler = std::make_shared<detail::Handler<Args...>>( connection, callback);
    
    handlerMap_.insert( std::make_pair( eventId, handler));
    return connection;
}

template <typename Func>
ConnectionSharedPtr EventEmitter::on(int eventId, Func callback)
{
    auto function = detail::toFunction( callback);
    
    static_assert( !std::is_same< decltype( function), Func>::value, "EventEmitter callback must accept only const values");

    return on( eventId, detail::toFunction( callback));
}

template <typename ...Args>
void EventEmitter::fire(int eventId, const Args&... args)
{
    std::list<Callback<Args...>> callbacks;
    
    {
        std::lock_guard<std::mutex> lock( handlerMapMutex_);
        
        auto range = handlerMap_.equal_range( eventId);
        for( auto it = range.first; it != range.second; ++it)
        {
            auto handler = std::dynamic_pointer_cast< detail::Handler<Args...>>(it->second);
            if(!handler)
                throw std::runtime_error("Event arguments mismatch");
            else
                callbacks.push_back( handler->callback);
        }
    }
        
    for(auto& callback: callbacks)
        callback( args...);
}

}

#endif // EVENT_EVENTEMITTER_H