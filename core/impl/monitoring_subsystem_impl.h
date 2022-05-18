/// \file monitoring_subsystem_impl.h
/// \brief определение реализации подсистемы мониторинга

#pragma once
#ifndef CORE_MONITORING_SUBSYSTEM_IMPL_H
#define CORE_MONITORING_SUBSYSTEM_IMPL_H

#include <core/interfaces/monitoring_subsystem.h>

#include <common/event_queue.hpp>
#include <common/monitoring_event.h>
#include <common/monitoring_options.h>

#include <memory>
#include <vector>
#include <thread>

namespace core
{

class MonitoringSubsystemImpl : public MonitoringSubsystem
{
public:
    /// \brief конструктор контроллера событий
    MonitoringSubsystemImpl(
        std::shared_ptr<common::EventQueue<common::MonitoringEvent>> queue);

    /// \brief деструктор контроллера событий
    ~MonitoringSubsystemImpl() override;

    /// \brief запуск контроллера событий
    void Run() override;

    /// \brief остановка контроллера событий
    void Stop() override;

private:

    /// \brief поток сбора данных
    void dataCollecting();

    /// \brief флаг работы потока
    bool isRunning_;

    /// \brief поток подсистемы
    std::thread subsystemThread_;

    /// \brief очередь событий
    std::shared_ptr<common::EventQueue<common::MonitoringEvent>> queue_;

    /// \brief структура настроек мониторинга
    std::shared_ptr<common::MonitoringOptions> options_;

};

}
#endif