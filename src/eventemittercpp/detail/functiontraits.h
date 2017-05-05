#ifndef FUNCTIONTRAITS_H
#define FUNCTIONTRAITS_H

#include <type_traits>

namespace event
{

namespace detail
{    
    
template <typename Function>
struct FunctionTraits : public FunctionTraits<decltype(&Function::operator())> 
{};

template <typename ClassType, typename ReturnType, typename... Args>
struct FunctionTraits<ReturnType(ClassType::*)(Args...) const> 
{
    typedef ReturnType (*pointer)(const Args&...);
    typedef const std::function<ReturnType(const Args&...)> function;
};

template <typename Function>
typename FunctionTraits<Function>::function toFunction (Function& lambda) 
{
    return static_cast<typename FunctionTraits<Function>::function>(lambda);
}

}
    
}
#endif // FUNCTIONTRAITS_H
