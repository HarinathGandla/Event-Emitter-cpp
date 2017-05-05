#include "connection.h"
#include "eventemitter.h"

namespace event
{
    
Connection::Connection(EventEmitter& emitter, int connectionId) :
    emitter_( emitter), id_( connectionId), isEmitterAlive_( true)
{}

Connection::~Connection()
{
    disconnect();
}

Connection::Connection(Connection&& other) :
    emitter_( other.emitter_),
    id_( other.id_),
    isEmitterAlive_( other.isEmitterAlive_)
{
    other.id_ = 0;
}

void Connection::notifyEmitterGone()
{
    isEmitterAlive_ = false;
}

int Connection::getId() const
{
    return id_;
}

void Connection::disconnect()
{
    if( id_ && isEmitterAlive_)
    {
        emitter_.removeHandler( id_);
        id_ = 0;
    }
}



    
}
