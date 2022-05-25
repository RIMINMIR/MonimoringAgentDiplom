/// \file transport_subsystem.h
/// \brief определение интерфейса доступа к подсистеме мониторинга

#pragma once
#ifndef CORE_TRANSPORT_SUBSYSTEM_H
#define CORE_TRANSPORT_SUBSYSTEM_H

#include <common/monitoring_data_structures.h>
#include <common/event_queue/monitoring_event.h>

#include <vector>

namespace core
{

struct TransportSubsystem
{
    /// \brief деструктор транспортной подсистемы
    virtual ~TransportSubsystem() = default;

     /// \brief запуск транспортной подсистемы
    virtual void Run() = 0;

    /// \brief остановка транспортной подсистемы
    virtual void Stop() = 0;

    /// \brief отправка собранных данных на сервера мониторинга
    /// \param data вектор с собранными метриками
    virtual void SendMonitoringData(std::vector<common::MonitoringData>& data) = 0;

    /// \brief отправка произошедшего события на сервер мониторинга
    /// \param event событие, отправка которого необходима
    virtual void SendMonitoringEvent(common::MonitoringEvent& event) = 0;
};

}
#endif