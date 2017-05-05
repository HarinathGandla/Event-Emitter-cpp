#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <functional>

#include "../connection.h"

namespace event 
{
    
namespace detail
{

struct HandlerBase 
{
    HandlerBase( const ConnectionSharedPtr& connection);
    virtual ~HandlerBase();
      
    ConnectionWeakPtr connection;
    int connectionId;
};

template <typename ...Args>
struct Handler : HandlerBase
{
    using Callback = std::function< void(const Args&...)>;
    
    Handler( const ConnectionSharedPtr& connection, Callback callback);
    
    Callback callback;
};

using HandlerPtr = std::shared_ptr<HandlerBase>;

template <typename ...Args>
Handler<Args...>::Handler(const ConnectionSharedPtr& connection, Handler::Callback callback) : 
    HandlerBase(connection), callback( callback)
{}


}
    
}

#endif // EVENT_HANDLER_H
