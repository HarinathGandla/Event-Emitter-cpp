#ifndef EVENT_CONNECTION_H
#define EVENT_CONNECTION_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <list>

namespace event
{
    
class EventEmitter;

class Connection : boost::noncopyable, public std::enable_shared_from_this<Connection>
{
public:
    Connection( EventEmitter& emitter, int connectionId);
    ~Connection();
    
    Connection(Connection&& other);
    
    int getId() const;    
    void notifyEmitterGone();
    
    void disconnect();
    
private:
    EventEmitter& emitter_;
    int id_;
    bool isEmitterAlive_;
};

using ConnectionWeakPtr = std::weak_ptr<Connection>;
using ConnectionSharedPtr = std::shared_ptr<Connection>;
using ConnectionList = std::list<ConnectionSharedPtr>;

}

#endif // EVENT_CONNECTION_H
