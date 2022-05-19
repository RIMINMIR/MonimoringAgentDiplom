/// \file event_queue_test.cpp
/// \brief Тесты для проверки функциональности очереди событий

#include <common/event_queue/event_queue.hpp>
#include <common/event_queue/monitoring_event.h>


#include <gtest/gtest.h>

#include <future>
#include <chrono>
#include <stdint.h>
#include <vector>
#include <thread>
#include <map>

using namespace common;

constexpr uint32_t MaxThreadMessages = 100;
constexpr uint32_t MaxThreads = 100;
constexpr uint32_t MaxIterations = MaxThreads * MaxThreadMessages;
constexpr uint32_t TestValue = 42;


/// \brief функция, добавляющая элементы в очередь и устанавливающая промис
/// \param queue ссылка на очередь сообщений
/// \param spPromise промис хранящий состояние потока(true если пото завершён, иначе false)
/// \param threadId номер потока
void QueuePushWithPromisethread(EventQueue<MonitoringEvent> &queue, std::promise<bool> &spPromise,
     const uint32_t threadId)
{
     TestEvent testData(threadId);
     for (uint32_t i = 0; i <MaxThreadMessages; i++)
     {
          queue.Push(testData);
     }
     spPromise.set_value_at_thread_exit(true);
}


/// \brief функция, добавляющая элементы в очередь
/// \param queue ссылка на очередь сообщений
/// \param threadId номер потока
void QueuePushthread(EventQueue<AgentEvent<uint32_t>> &queue, const uint32_t threadId)
{
     AgentEvent<uint32_t> testData(threadId);
     for (uint32_t i = 0; i <MaxThreadMessages;i++)
     {
          queue.Push(testData);
     }
}

/// \brief функция проверяющая, что все сообщения для каждого потока из map приняты
/// \param messages map ключами которого являются id потоков а значениями количество полученных от них сообщений
bool CheckMap(const std::map<uint32_t, uint32_t>& messages)
{
     for (const auto& message : messages)
     {
          if (message.second != MaxThreadMessages)
          {
               return false;
          }
     }
     return true;
}

/// \brief функция, добавляющая в очередь один элемент
/// \param queue ссылка на очередь сообщений
/// \param data сообщение помещаемое функцией в очередь
void OnePushThread(const AgentEvent<uint32_t> &data, EventQueue<AgentEvent<uint32_t>> &queue)
{
     queue.Push(data);
}

/// \brief функция, ожидающая одно событие из очереди
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void WaitPopThread(AgentEvent<uint32_t> &data, EventQueue<AgentEvent<uint32_t>> &queue)
{
     queue.WaitAndPop(data);
}

/// \brief функция, ожидающая одно событие из очереди и меняющая параметра data после завершения ожидания
/// \param queue ссылка на очередь сообщений
/// \param data изменяемое значение
void WaitAndChangeThread(AgentEvent<uint32_t> &data, EventQueue<AgentEvent<uint32_t>> &queue)
{
     queue.WaitAndPop();
     data = AgentEvent<uint32_t>{TestValue};
}

/// \brief функция, ожидающая одно событие из очереди через sharedPtr
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void WaitPtrThread(AgentEvent<uint32_t> &data, EventQueue<AgentEvent<uint32_t>> &queue)
{
     data = *queue.WaitAndPop();
}

/// \brief функция, пытающаяся получить одно событие из очереди в цикле
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void OnePopThread(AgentEvent<uint32_t> &data, EventQueue<AgentEvent<uint32_t>> &queue)
{
     while(!queue.TryPop(data))
     {
     }
}

/// \brief функция, загружающая событие из очереди если она не пуста
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void OnePopPtrThread(AgentEvent<uint32_t> &data, EventQueue<AgentEvent<uint32_t>> &queue)
{
     if (!queue.Empty())
     {
          data = *queue.Pop();
     }
}

/// \brief Проверяет корректность выполнения метода Pop, возвращающего значение элемента
TEST(QueueFunctionsTests, PopTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);
     AgentEvent<uint32_t> testData(TestValue);
     AgentEvent<uint32_t> testPopData = {};
     std::thread waitingThread(OnePopThread, std::ref(testPopData), std::ref(queue));
     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));
     pushingThread.detach();
     waitingThread.join();
     ASSERT_EQ(testPopData.Load(), testData.Load());
}

/// \brief Проверяет корректность выполнения метода Pop, возвращающего указатель на элемент
TEST(QueueFunctionsTests, PopPtrTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);

     AgentEvent<uint32_t> testData(TestValue);
     AgentEvent<uint32_t> testPopData = {};

     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));
     std::thread waitingThread(OnePopPtrThread, std::ref(testPopData), std::ref(queue));

     pushingThread.detach();
     waitingThread.join();

     ASSERT_EQ(testPopData.Load(), testData.Load());
}

/// \brief Проверяет корректность выполнения метода WaitAndPop, возвращающего значения
TEST(QueueFunctionsTests, WaitAndPopTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);

     AgentEvent<uint32_t> testData(TestValue);
     AgentEvent<uint32_t> testPopData = {};

     std::thread waitingThread(WaitPopThread,std::ref(testPopData), std::ref(queue));
     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));

     pushingThread.detach();
     waitingThread.join();

     ASSERT_EQ(testPopData.Load(), testData.Load());
}

/// \brief Проверяет корректность выполнения метода Pop, возвращающего указатель на элемент
TEST(QueueFunctionsTests, WaitAndPopPtrTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);

     AgentEvent<uint32_t> testData(TestValue);
     AgentEvent<uint32_t> testPopData = {};

     std::thread waitingThread(WaitPtrThread,std::ref(testPopData), std::ref(queue));
     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));

     pushingThread.detach();
     waitingThread.join();

     ASSERT_EQ(testPopData.Load(), testData.Load());
}

/// \brief Проверяет корректность выполнения метода Empty, проверяющего очередь на пустоту
TEST(QueueFunctionsTests, EmptyTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);

     AgentEvent<uint32_t> testData(TestValue);
     AgentEvent<uint32_t> testPopData = {};

     ASSERT_TRUE(queue.Empty());

     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));

     pushingThread.join();
     ASSERT_FALSE(queue.Empty());
}

/// \brief Проверяет корректность выполнения метода Size, возвращающего размер очереди
TEST(QueueFunctionsTests, SizeTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);
     AgentEvent<uint32_t> testData(TestValue);

     ASSERT_EQ(queue.Size(), 0U);
     queue.Push(testData);
     ASSERT_EQ(queue.Size(), 1U);
}

/// \brief Проверяет корректность выполнения метода StopWait, заверщающего ожидание элемента из очереди
TEST(QueueFunctionsTests, DISABLED_StopWaitTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);

     AgentEvent<uint32_t> testData(0);
     AgentEvent<uint32_t> testPopData = {};

     std::thread pushingThread(WaitAndChangeThread, std::ref(testData), std::ref(queue));

     ASSERT_EQ(*testData.Load(), 0U);
     std::this_thread::sleep_for(std::chrono::microseconds(100));

     queue.StopWait();
     if(pushingThread.joinable())
     {
          pushingThread.join();
     }
     ASSERT_EQ(*testData.Load(), TestValue);
}

/// \brief Проверяет потокобезопасность метода WaitAndPop, возвращающего указатель на значение элемента
TEST(QueuethreadSafetyTests, WaitAndPopPtrPromiseTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);
     std::vector<std::thread> threads(MaxThreads);

     std::vector<std::promise<bool>> spPromises(MaxThreads);
     std::vector<std::future<bool>> waiters(MaxThreads);

     constexpr auto receivedMessageCount = 0;

     // map ключами которого являются идентификаторы потоков, а значениями количество полученных сообщений от потока
     std::map<uint32_t, uint32_t> messages = {};
     for (uint32_t threadIndex = 0; threadIndex < MaxThreads; ++threadIndex)
     {
          waiters[threadIndex] = spPromises[threadIndex].get_future() ;
          threads[threadIndex] = std::thread{QueuePushWithPromisethread, std::ref(queue), std::ref(spPromises[threadIndex]), threadIndex};
          messages.insert(std::make_pair(threadIndex, receivedMessageCount));
     }

     for (uint32_t threadIndex = 0; threadIndex < MaxThreads; ++threadIndex)
     {
          threads[threadIndex].join();
     }

     for (uint32_t threadIndex = 0; threadIndex < MaxThreads; ++threadIndex)
     {
          ASSERT_TRUE(waiters[threadIndex].get());
     }

     for (uint32_t interIndex = 0; interIndex < MaxIterations; ++interIndex)
     {
          const auto testData = queue.WaitAndPop();
          const auto threadId = *(testData ->Load());
          ++messages[threadId];
     }

     ASSERT_TRUE(CheckMap(messages));
}

/// \brief Проверяет потокобезопасность метода Pop возвращающего указатель на значение элемента
TEST(QueuethreadSafetyTests, PopPtrTest)
{
     EventQueue<AgentEvent<uint32_t>> queue(MaxIterations);
     std::vector<std::thread> threads(MaxThreads);

     constexpr auto receivedMessageCount = 0;

     // map ключами которого являются идентификаторы потоков, а значениями количество полученных сообщений от потока
     std::map<uint32_t, uint32_t> messages = {};

     for (uint32_t threadIndex = 0; threadIndex < MaxThreads; ++threadIndex)
     {
          threads[threadIndex] = std::thread{QueuePushthread, std::ref(queue), threadIndex};
          messages.insert(std::make_pair(threadIndex, receivedMessageCount));
     }

     for (uint32_t threadIndex = 0; threadIndex < MaxThreads; ++threadIndex)
     {
          threads[threadIndex].join();
     }

     while(!queue.Empty())
     {
          const auto data = queue.Pop();
          const auto threadId = *(data->Load());
          ++messages[threadId];
     }

     ASSERT_TRUE(CheckMap(messages));
}