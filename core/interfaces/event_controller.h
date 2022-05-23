/// \file event_controller.h
/// \brief определение интерфейса контроллера событий

#pragma once
#ifndef CORE_EVENT_CONTROLLER_H
#define CORE_EVENT_CONTROLLER_H

#include <common/event_queue/monitoring_event.h>

namespace core
{

struct EventController
{
    /// \brief деструктор контроллера событий
    virtual ~EventController() = default;

    /// \brief запуск контроллера событий
    virtual void Run() = 0;

    /// \brief остановка контроллера событий
    virtual void Stop() = 0;

    /// \brief помещение события на обработку
    /// \param event помещаемое событие
    virtual void PutEvent(common::MonitoringEvent& event);
};

}
#endif