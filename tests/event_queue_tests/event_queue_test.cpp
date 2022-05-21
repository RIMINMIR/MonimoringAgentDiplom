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
     TestEvent testData = {threadId};
     common::MonitoringEvent monitoringData = {testData};
     for (uint32_t i = 0; i <MaxThreadMessages; i++)
     {
          queue.Push(monitoringData);
     }
     spPromise.set_value_at_thread_exit(true);
}


/// \brief функция, добавляющая элементы в очередь
/// \param queue ссылка на очередь сообщений
/// \param threadId номер потока
void QueuePushthread(EventQueue<MonitoringEvent> &queue, const uint32_t threadId)
{
     TestEvent testData = {threadId};
     common::MonitoringEvent monitoringData = {testData};
     for (uint32_t i = 0; i <MaxThreadMessages;i++)
     {
          queue.Push(monitoringData);
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
void OnePushThread(const MonitoringEvent &data, EventQueue<MonitoringEvent> &queue)
{
     queue.Push(data);
}

/// \brief функция, ожидающая одно событие из очереди
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void WaitPopThread(MonitoringEvent &data, EventQueue<MonitoringEvent> &queue)
{
     data = *(queue.WaitAndPop());
}

/// \brief функция, ожидающая одно событие из очереди и меняющая параметра data после завершения ожидания
/// \param queue ссылка на очередь сообщений
/// \param data изменяемое значение
void WaitAndChangeThread(MonitoringEvent &data, EventQueue<MonitoringEvent> &queue)
{
     queue.WaitAndPop();
     TestEvent testEvent = {TestValue};
     data = MonitoringEvent{testEvent};
}

/// \brief функция, ожидающая одно событие из очереди через sharedPtr
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void WaitPtrThread(MonitoringEvent &data, EventQueue<MonitoringEvent> &queue)
{
     data = *queue.WaitAndPop();
}

/// \brief функция, пытающаяся получить одно событие из очереди в цикле
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void OnePopThread(MonitoringEvent &data, EventQueue<MonitoringEvent> &queue)
{
     std::shared_ptr<MonitoringEvent> temp = nullptr;
     while(!queue.TryPop(temp))
     {
     }
     data = *temp;
}

/// \brief функция, загружающая событие из очереди если она не пуста
/// \param queue ссылка на очередь сообщений
/// \param data сообщение загружаемое из очереди
void OnePopPtrThread(MonitoringEvent &data, EventQueue<MonitoringEvent> &queue)
{
     if (!queue.Empty())
     {
          data = *queue.Pop();
     }
}

/// \brief Проверяет корректность выполнения метода Pop, возвращающего значение элемента
TEST(QueueFunctionsTests, PopTest)
{
     EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {TestValue};
     MonitoringEvent testData(testEvent);
     MonitoringEvent testPopData = {};
     std::thread waitingThread(OnePopThread, std::ref(testPopData), std::ref(queue));
     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));
     pushingThread.join();
     waitingThread.join();
     ASSERT_EQ(std::get<TestEvent>(testPopData).testDigit_, std::get<TestEvent>(testData).testDigit_);
}

/// \brief Проверяет корректность выполнения метода Pop, возвращающего указатель на элемент
TEST(QueueFunctionsTests, PopPtrTest)
{
     EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {TestValue};
     MonitoringEvent testData(testEvent);
     MonitoringEvent testPopData = {};

     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));
     std::thread waitingThread(OnePopPtrThread, std::ref(testPopData), std::ref(queue));

     pushingThread.detach();
     waitingThread.join();

     ASSERT_EQ(std::get<TestEvent>(testPopData).testDigit_, std::get<TestEvent>(testData).testDigit_);
}

/// \brief Проверяет корректность выполнения метода WaitAndPop, возвращающего значения
TEST(QueueFunctionsTests, WaitAndPopTest)
{
     EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {TestValue};
     MonitoringEvent testData(testEvent);
     MonitoringEvent testPopData = {};

     std::thread waitingThread(WaitPopThread,std::ref(testPopData), std::ref(queue));
     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));

     pushingThread.detach();
     waitingThread.join();

     ASSERT_EQ(std::get<TestEvent>(testPopData).testDigit_, std::get<TestEvent>(testData).testDigit_);
}

/// \brief Проверяет корректность выполнения метода Pop, возвращающего указатель на элемент
TEST(QueueFunctionsTests, WaitAndPopPtrTest)
{
     EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {TestValue};
     MonitoringEvent testData(testEvent);
     MonitoringEvent testPopData = {};

     std::thread waitingThread(WaitPtrThread,std::ref(testPopData), std::ref(queue));
     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));

     pushingThread.detach();
     waitingThread.join();

     ASSERT_EQ(std::get<TestEvent>(testPopData).testDigit_, std::get<TestEvent>(testData).testDigit_);
}

/// \brief Проверяет корректность выполнения метода Empty, проверяющего очередь на пустоту
TEST(QueueFunctionsTests, EmptyTest)
{
     EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {TestValue};
     MonitoringEvent testData(testEvent);
     MonitoringEvent testPopData = {};

     queue.Empty();

     std::thread pushingThread(OnePushThread, std::ref(testData), std::ref(queue));

     pushingThread.join();
     ASSERT_FALSE(queue.Empty());
}

/// \brief Проверяет корректность выполнения метода Size, возвращающего размер очереди
TEST(QueueFunctionsTests, SizeTest)
{
     EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {TestValue};
     MonitoringEvent testData(testEvent);

     ASSERT_EQ(queue.Size(), 0U);
     queue.Push(testData);
     ASSERT_EQ(queue.Size(), 1U);
}

/// \brief Проверяет корректность выполнения метода StopWait, заверщающего ожидание элемента из очереди
TEST(QueueFunctionsTests, StopWaitTest)
{
    EventQueue<MonitoringEvent> queue;
     TestEvent testEvent = {0};
     MonitoringEvent testData(testEvent);
     MonitoringEvent testPopData = {};

     std::thread pushingThread(WaitAndChangeThread, std::ref(testData), std::ref(queue));
     auto data = std::get<TestEvent>(testData);
     ASSERT_EQ(data.testDigit_, 0U);
     std::this_thread::sleep_for(std::chrono::microseconds(100));

     queue.StopWait();
     if(pushingThread.joinable())
     {
          pushingThread.join();
     }
     auto result = std::get<TestEvent>(testData);
     ASSERT_EQ(result.testDigit_, TestValue);
}

/// \brief Проверяет потокобезопасность метода WaitAndPop, возвращающего указатель на значение элемента
TEST(QueuethreadSafetyTests, WaitAndPopPtrPromiseTest)
{
     EventQueue<MonitoringEvent> queue;
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
          auto event = std::get<TestEvent>(*testData);
          const auto threadId = event.testDigit_;
          ++messages[threadId];
     }

     ASSERT_TRUE(CheckMap(messages));
}

/// \brief Проверяет потокобезопасность метода Pop возвращающего указатель на значение элемента
TEST(QueuethreadSafetyTests, PopPtrTest)
{
     EventQueue<MonitoringEvent> queue;
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
          auto event = std::get<TestEvent>(*data);
          const auto threadId = event.testDigit_;
          ++messages[threadId];
     }

     ASSERT_TRUE(CheckMap(messages));
}