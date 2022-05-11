/// \file event_queue
/// \brief шаблонный класс потокобезопасной оереди событий

#pragma once
#ifndef COMMON_EVENT_QUEUE
#define COMMON_EVENT_QUEUE

#include <queue>
#include <mutex>
#include <memory>

namespace common
{

/// \brief потокобезопасная очередь для работы с ней нескольких потоков
template<typename T>
class EventQueue
{

public:
    EventQueue();

    /// \brief помещение элемента в очередь
    /// \param new_value элемент
    void  push(T  new_value)
    {
        std::lock_guard<std::mutex>  lk(mut);
        dataQueue.push(std::move(data));
        data_cond.notify_one();
    }

    /// \brief ожидание и извлечение элемента из очереди
    /// \param value ссылка на элемент
    void WaitAndPop(T& value)
    {
        std::unique_lock<std::mutex>  lk(mut);
        data_cond.wait(lk,[this]{return  !dataQueue.empty();});
        value=std::move(dataQueue.front());
        dataQueue.pop();
    }

    /// \brief ожидание и извлечение элемента из очереди
    /// \return указатель на элемент
    std::shared_ptr<T> WaitAndPop()
    {
        std::unique_lock<std::mutex>  lk(mut);
        data_cond.wait(lk,[this]{return  !dataQueue.empty();});
        std::shared_ptr<T>  res(std::make_shared<T>(std::move(dataQueue.front())));
        dataQueue.pop();
        return  res;
    }

    /// \brief попытка извлечения элемента
    /// \param value ссылка на элемент
    /// \return true если удалось извлечь элемент
    bool  TryPop(T&  value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(dataQueue.empty())
        {
            return  false;
        }
        value=std::move(dataQueue.front());
        dataQueue.pop();
        return  true;
    }

    /// \brief попытка извлечения элемента
    /// \return указатель на извлекаемый элемент
    std::shared_ptr<T>  TryPop()
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

    /// \brief проверка очереди на пустоту
    /// \return true если очередь пуста
    bool  Empty()  const
    {
        std::lock_guard<std::mutex>  lk(mut);
        return  dataQueue.empty();
    }
private:
    mutable  std::mutex  mut;
    std::queue<T>  dataQueue;
    std::condition_variable  data_cond;

};

}

#endif