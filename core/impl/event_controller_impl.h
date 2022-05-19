/// \file event_controller.h
/// \brief определение реализации контроллера событий

#pragma once
#ifndef CORE_EVENT_CONTROLLER_IMPL_H
#define CORE_EVENT_CONTROLLER_IMPL_H

#include <core/interfaces/event_controller.h>

#include <common/event_queue/event_queue.hpp>
#include <common/event_queue/monitoring_event.h>

#include <memory>
#include <atomic>
#include <thread>

namespace core
{

class EventControllerImpl : public EventController
{
public:
    /// \brief конструктор контроллера событий
    EventControllerImpl(
        std::shared_ptr<common::EventQueue<common::MonitoringEvent>> queue);

    /// \brief деструктор контроллера событий
    ~EventControllerImpl() override;

    /// \brief запуск контроллера событий
    virtual void Run() override;

    /// \brief остановка контроллера событий
    virtual void Stop() override;

private:

    /// \brief флаг работы потока
    std::atomic_bool isRunning_;

    /// \brief основной поток обработки событий из очереди
    void processEvent();

    /// \brief поток обработки событий
    std::thread processEventThread_;

    /// \brief очередь событий
    std::shared_ptr<common::EventQueue<common::MonitoringEvent>> queue_;
};

}
#endif