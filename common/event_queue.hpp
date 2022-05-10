/// \file event_queue
/// \brief шаблонный класс потокобезопасной оереди событий

#pragma once
#ifndef COMMON_EVENT_QUEUE
#define COMMON_EVENT_QUEUE

#include <queue>
#include <mutex>
#include <memory>

template<typename T>
class threadsafe_queue
{

public:
    threadsafe_queue();

    /// \brief помещение элемента в очередь
    /// \param new_value элемент
    void  push(T  new_value)
    {
        std::lock_guard<std::mutex>  lk(mut);
        data_queue.push(std::move(data));
        data_cond.notify_one();
    }

    /// \brief ожидание и извлечение элемента из очереди
    /// \param value ссылка на элемент
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex>  lk(mut);
        data_cond.wait(lk,[this]{return  !data_queue.empty();});
        value=std::move(data_queue.front());      data_queue.pop();
    }

    /// \brief ожидание и извлечение элемента из очереди
    /// \return указатель на элемент
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex>  lk(mut);
        data_cond.wait(lk,[this]{return  !data_queue.empty();});
        std::shared_ptr<T>  res(      std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return  res;
    }

    /// \brief попытка извлечения элемента
    /// \param value ссылка на элемент
    /// \return true если удалось извлечь элемент
    bool  try_pop(T&  value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
        {
            return  false;
        }
        value=std::move(data_queue.front());
        data_queue.pop();
        return  true;
    }

    /// \brief попытка извлечения элемента
    /// \return указатель на извлекаемый элемент
    std::shared_ptr<T>  try_pop()
    {
        std::lock_guard<std::mutex>  lk(mut);
        if(data_queue.empty())
        {
            return  std::shared_ptr<T>();
        }
        std::shared_ptr<T>  res(      std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return  res;
    }

    /// \brief проверка очереди на пустоту
    /// \return true если очередь пуста
    bool  empty()  const
    {
        std::lock_guard<std::mutex>  lk(mut);
        return  data_queue.empty();
    }
private:
    mutable  std::mutex  mut;
    std::queue<T>  data_queue;
    std::condition_variable  data_cond;

};

#endif