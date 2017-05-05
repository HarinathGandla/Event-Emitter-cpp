#ifndef EVENT_EVENTEMITTERTEST_H
#define EVENT_EVENTEMITTERTEST_H

#include <gtest/gtest.h>

#include "eventemittercpp/eventemitter.h"

namespace event 
{

class EventEmitterTest : public testing::Test
{
};

TEST_F( EventEmitterTest, shouldCallEventHandler)
{
    int testEventId = 1;
    int testArgumentValue = 100;
    EventEmitter emitter;
    
    auto conn = emitter.on( testEventId, [ testArgumentValue]( int value){
        ASSERT_EQ( testArgumentValue, value);
    });
    
    emitter.fire( testEventId, testArgumentValue);
}

TEST_F( EventEmitterTest, shouldCallAllEventHandlers)
{
    int testEventId = 1;
    EventEmitter emitter;
    
    int callCount = 0;
    
    auto conn = emitter.on( testEventId, [ &callCount](){
        ++callCount;
    });
    
    auto conn1 = emitter.on( testEventId, [ &callCount](){
        ++callCount;
    });
    
    emitter.fire( testEventId);
    ASSERT_EQ( callCount, 2);
}

TEST_F( EventEmitterTest, shouldThrowExceptionOnArgumentMismatch)
{
    EXPECT_THROW({
            int testEventId = 1;
            EventEmitter emitter;
            
            auto conn = emitter.on( testEventId, []( int value){
                FAIL();
            });
            
            emitter.fire( testEventId, "");
        },
        std::runtime_error
    );
}

TEST_F( EventEmitterTest, shouldNotCallDisconnectedEventHandler)
{
    int testEventId = 1;
    EventEmitter emitter;
    
    auto connection = emitter.on( testEventId, [](){
        FAIL();
    });
    
    connection->disconnect();
    
    emitter.fire( testEventId);
}

TEST_F( EventEmitterTest, shouldConnectionLifeTimeIsItsScope)
{
    int testEventId = 1;
    EventEmitter emitter;
    
    {
        auto connection = emitter.on( testEventId, [](){
            FAIL();
        });
    }
    
    emitter.fire( testEventId);
}

TEST_F( EventEmitterTest, shouldAcceptConstRefEventArgs)
{
    int testEventId = 1;
    auto testArg = "test";
    EventEmitter emitter;
    
    {
        auto connection = emitter.on( testEventId, [testArg]( const std::string& arg){
            ASSERT_EQ( testArg, arg);
        });
    }
    
    emitter.fire( testEventId, testArg);
    emitter.fire( testEventId, const_cast< const decltype(testArg)>( testArg));
}

TEST_F( EventEmitterTest, shouldAcceptConstEventArgs)
{
    int testEventId = 1;
    auto testArg = "test";
    EventEmitter emitter;
    
    {
        auto connection = emitter.on( testEventId, [testArg]( const std::string arg){
            ASSERT_EQ( testArg, arg);
        });
    }
    
    emitter.fire( testEventId, testArg);
    emitter.fire( testEventId, const_cast< const decltype(testArg)>( testArg));
}

TEST_F( EventEmitterTest, shouldAcceptValueEventArgs)
{
    int testEventId = 1;
    auto testArg = "test";
    EventEmitter emitter;
    
    {
        auto connection = emitter.on( testEventId, [testArg]( std::string arg){
            ASSERT_EQ( testArg, arg);
        });
    }
    
    emitter.fire( testEventId, testArg);
    emitter.fire( testEventId, const_cast< const decltype(testArg)>( testArg));
}

}

#endif // EVENT_EVENTEMITTERTEST_H
