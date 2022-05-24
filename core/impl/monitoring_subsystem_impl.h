/// \file monitoring_subsystem_impl.h
/// \brief определение реализации подсистемы мониторинга

#pragma once
#ifndef CORE_MONITORING_SUBSYSTEM_IMPL_H
#define CORE_MONITORING_SUBSYSTEM_IMPL_H

#include <core/interfaces/monitoring_subsystem.h>
#include <core/interfaces/data_collector.h>
#include <core/interfaces/event_controller.h>
#include <core/interfaces/data_collector.h>

#include <common/event_queue/event_queue.hpp>
#include <common/event_queue/monitoring_event.h>

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
    MonitoringSubsystemImpl(std::shared_ptr<EventController> controller, CollectorList collectors);

    /// \brief деструктор контроллера событий
    ~MonitoringSubsystemImpl() override;

    /// \brief запуск контроллера событий
    void Run() override;

    /// \brief остановка контроллера событий
    void Stop() override;

private:

    /// \brief поток сбора данных
    void dataCollecting();

    /// \brief поток отправки данных
    void dataSending();

    /// \brief флаг работы потока
    bool isRunning_;

    /// \brief поток сбора данных
    std::thread collectingThread_;

    /// \brief поток отправки данных
    std::thread sendingThread_;

    /// \brief структура настроек мониторинга
    std::shared_ptr<common::MonitoringOptions> options_;

    /// \brief вектор сборщиков данных
    CollectorList collectors_;

    /// \brief указаель на контроллер событий для отправки ему событий
    std::shared_ptr<EventController> events_;

};

}
#endif