#ifndef __THREAD_MANAGER_CPP
#define __THREAD_MANAGER_CPP
#include<threadmanager>
#include<thread>
#include<tuple>
#include<utility>
#include<functional>
#include<type_traits>
using namespace std;
template<typename pointer_to_function,typename ...T>
ThreadManager<pointer_to_function,T...>::ThreadManager(pointer_to_function f,T&&... argu):func(f),arguments(forward<T>(argu)...),thread_ptr(NULL){}

template<typename pointer_to_function,typename ...T>
ThreadManager<pointer_to_function,T...>::~ThreadManager()
{
if(this->thread_ptr)
{
this->thread_ptr->join();
delete this->thread_ptr;
}
}

template<typename pointer_to_function, typename... T>
template<size_t... c>
void ThreadManager<pointer_to_function, T...>::threadStarter(tuple<T...> &t, index_sequence<c...>) {
    this->thread_ptr = new thread([this, &t]() {
        invoke(this->func, forward_as_needed(get<c>(t))...);
    });
}
/*
template<typename pointer_to_function,typename ...T>
template<size_t ...c>
void ThreadManager<pointer_to_function,T...>::threadStarter(tuple<dacay_t<T>...> &t,index_sequence<c...>)
{
this->thread_ptr=new thread([this,&t](){invoke(this->func,get<c>(t)...);});
}
*/
template<typename pointer_to_function,typename ...T>
void ThreadManager<pointer_to_function,T...>::start()
{
threadStarter(this->arguments,index_sequence_for<T...>());
}
#endif
