/// \file transport_subsystem_impl.h
/// \brief определение реализации транспортной подсистемы

#pragma once
#ifndef CORE_TRANSPORT_SUBSYSTEM_IMPL_H
#define CORE_TRANSPORT_SUBSYSTEM_IMPL_H

#include <core/interfaces/transport_subsystem.h>

namespace core
{

class TransportSubsystemImpl : public TransportSubsystem
{
public:
    /// \brief конструктор контроллера событий
    TransportSubsystemImpl();

    /// \brief деструктор контроллера событий
    ~TransportSubsystemImpl() override;

    /// \brief отправка собранных данных на сервера мониторинга
    /// \param data вектор с собранными метриками
    virtual void SendMonitoringData(std::vector<common::MonitoringData>& data) override;

    /// \brief отправка произошедшего события на сервер мониторинга
    /// \param event событие, отправка которого необходима
    virtual void SendMonitoringEvent(common::MonitoringEvent& event) override;

private:


};

}

#endif
