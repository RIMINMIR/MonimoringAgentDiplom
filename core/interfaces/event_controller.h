/// \file event_controller.h
/// \brief определение интерфейса контроллера событий

#pragma once
#ifndef CORE_EVENT_CONTROLLER_H
#define CORE_EVENT_CONTROLLER_H


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
};

}
#endif