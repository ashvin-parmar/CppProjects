#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <thread>
#include <tuple>
#include <utility>
#include <functional>
#include <type_traits>

template<typename Func, typename... Args>
class ThreadManager {
public:
    ThreadManager(Func f, Args&&... args);
    ~ThreadManager();

    void start();

private:
    Func func;
    std::tuple<std::decay_t<Args>...> arguments;
    std::thread* thread_ptr;

    template<size_t... Indices>
    void threadStarter(std::index_sequence<Indices...>);
/*
    template<typename T>
    auto wrapper(T&& t) -> decltype(std::forward<T>(t)) { return std::forward<T>(t); }

    template<typename T>
    auto wrapper(std::reference_wrapper<T> t) -> T& { return t.get(); }
*/
};

template<typename Func, typename... Args>
ThreadManager<Func, Args...>::ThreadManager(Func f, Args&&... args)
    : func(f), arguments(std::forward<Args>(args)...), thread_ptr(nullptr) {}

template<typename Func, typename... Args>
ThreadManager<Func, Args...>::~ThreadManager() {
    if (this->thread_ptr) {
        this->thread_ptr->join();
        delete this->thread_ptr;
    }
}

template<typename Func, typename... Args>
template<size_t... Indices>
void ThreadManager<Func, Args...>::threadStarter(std::index_sequence<Indices...>) {
    this->thread_ptr = new thread([this]() {
        invoke(this->func,forward<Args>(get<Indices>(this->arguments))...);
    });
}

template<typename Func, typename... Args>
void ThreadManager<Func, Args...>::start() {
    threadStarter(std::index_sequence_for<Args...>{});
}

#endif // THREAD_MANAGER_H
