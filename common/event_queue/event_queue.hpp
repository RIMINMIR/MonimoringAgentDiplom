/// \file event_queue
/// \brief шаблонный класс потокобезопасной оереди событий

#pragma once
#ifndef COMMON_EVENT_QUEUE
#define COMMON_EVENT_QUEUE

#include <queue>
#include <mutex>
#include <memory>
#include <atomic>

namespace common
{

/// \brief потокобезопасная очередь для работы с ней нескольких потоков
template<typename T>
class EventQueue
{

public:

    /// \brief помещение элемента в очередь
    /// \param new_value элемент
    void  Push(T  new_value)
    {
        std::lock_guard<std::mutex>  lk(mut);
        dataQueue.push(std::move(new_value));
        stop_wait.store(false);
        data_cond.notify_one();
    }

    /// \brief ожидание и извлечение элемента из очереди
    /// \return указатель на элемент
    std::shared_ptr<T> WaitAndPop()
    {
        std::unique_lock<std::mutex>  lk(mut);
        data_cond.wait(lk,[this]{return  !dataQueue.empty() || stop_wait.load() == true;});
        if(stop_wait.load() == true)
        {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T>  res(std::make_shared<T>(std::move(dataQueue.front())));
        dataQueue.pop();
        return  res;
    }

    /// \brief попытка извлечения элемента
    /// \return указатель на извлекаемый элемент
    std::shared_ptr<T>  Pop()
    {
        std::lock_guard<std::mutex>  lk(mut);
        if(dataQueue.empty())
        {
            return  std::shared_ptr<T>();
        }
        std::shared_ptr<T>  res(std::make_shared<T>(std::move(dataQueue.front())));
        dataQueue.pop();
        return  res;
    }

    /// \brief попытка извлечения элемента
    /// \param elem извлекаемый элемент
    /// \return true в случае успеха, иначе false
    bool  TryPop(std::shared_ptr<T>& elem)
    {
        std::lock_guard<std::mutex>  lk(mut);
        if(dataQueue.empty())
        {
            return  false;
        }
        std::shared_ptr<T>  res(std::make_shared<T>(std::move(dataQueue.front())));
        dataQueue.pop();
        elem = res;
        return  true;
    }

    /// \brief проверка очереди на пустоту
    /// \return true если очередь пуста
    bool  Empty()  const
    {
        std::lock_guard<std::mutex>  lk(mut);
        return  dataQueue.empty();
    }

       /// \brief проверка очереди на пустоту
    /// \return true если очередь пуста
    size_t  Size()  const
    {
        std::lock_guard<std::mutex>  lk(mut);
        return  dataQueue.size();
    }

    /// \brief остановка ожидания элементов из очереди
    void StopWait()
    {
        stop_wait.store(true);
        data_cond.notify_one();
    }

private:
    mutable  std::mutex  mut;
    std::queue<T>  dataQueue;
    std::condition_variable  data_cond;
    std::atomic<bool> stop_wait;

};

}

#endif