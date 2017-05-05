#include "handler.h"

namespace event
{
    
namespace detail
{


HandlerBase::HandlerBase(const ConnectionSharedPtr& connection) :
    connection( connection),
    connectionId( connection->getId())
{}

HandlerBase::~HandlerBase()
{
    auto ptr = connection.lock();
    if( ptr)
        ptr->notifyEmitterGone();
}

}

}