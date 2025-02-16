#pragma once
#include "threadpool.hpp"

#include <atomic>
#include <bits/chrono.h>
#include <mutex>

//--------------------------------------------------------------------------------------------------------
// Define Singleton Threads pool
//--------------------------------------------------------------------------------------------------------
template <typename DataType>
    requires threadspool::isTrival<DataType>
std::mutex threadspool::ThreadsPool<DataType>::m_singleton;

template <typename DataType>
    requires threadspool::isTrival<DataType>
std::atomic<threadspool::ThreadsPool<DataType> *> threadspool::ThreadsPool<DataType>::m_instance;

template <typename DataType>
    requires threadspool::isTrival<DataType>
threadspool::ThreadsPool<DataType> *threadspool::ThreadsPool<DataType>::instance(int _num)
{
    auto ins_ptr = ThreadsPool<DataType>::m_instance.load(std::memory_order_acquire);
    if (ins_ptr == nullptr)
    {
        std::lock_guard<std::mutex> lk{ThreadsPool<DataType>::m_singleton};
        ins_ptr = ThreadsPool<DataType>::m_instance.load(std::memory_order_relaxed);
        if (ins_ptr == nullptr)
        {
            ins_ptr = new ThreadsPool<DataType>();
            ThreadsPool<DataType>::m_instance.store(ins_ptr, std::memory_order_release);
        }
    }

    return ins_ptr;
}

//--------------------------------------------------------------------------------------------------------
// True thread pool ctor and dtor
//--------------------------------------------------------------------------------------------------------
template <typename DataType>
    requires threadspool::isTrival<DataType>
threadspool::ThreadsPool<DataType>::ThreadsPool() : m_stop(false)
{}

template <typename DataType>
    requires threadspool::isTrival<DataType>
threadspool::ThreadsPool<DataType>::~ThreadsPool()
{}