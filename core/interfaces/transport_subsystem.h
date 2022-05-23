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

    /// \brief отправка собранных данных на сервера мониторинга
    /// \param data вектор с собранными метриками
    virtual void SendMonitoringData(std::vector<common::MonitoringData>& data);

    /// \brief отправка произошедшего события на сервер мониторинга
    /// \param event событие, отправка которого необходима
    virtual void SendMonitoringEvent(common::MonitoringEvent& event);
};

}
#endif