/// \file core_impl.h
/// \brief определение реализации ядра службы

#pragma once
#ifndef CORE_CORE_IMPL_H
#define CORE_CORE_IMPL_H

#include <core/interfaces/core.h>
#include <core/interfaces/data_collector.h>
#include <core/interfaces/event_controller.h>
#include <core/interfaces/monitoring_subsystem.h>
#include <core/interfaces/storage_controller.h>
#include <core/impl/transport_subsystem_impl.h>

#include <common/core_content.h>
#include <common/event_queue/event_queue.hpp>

#include <memory>

namespace core
{

class CoreImpl : public Core
{
public:
    /// \brief конструктор
    /// \param content компоненты передаваемые в ядро
    CoreImpl(common::CoreContent& content);

    /// \brief деструктор
    ~CoreImpl() override;

    /// \brief запуск ядра службы
    void Run() override;

    /// \brief остановка ядра службы
    void Stop() override;

private:

    /// \brief интерфейс контроллера событий
    std::shared_ptr<EventController> eventController_;

    /// \brief интерфейс подсистемы мониторинга
    std::shared_ptr<MonitoringSubsystem> monitoringSubsystem_;

    /// \brief интерфейс контроллера внутреннего хранилища
    std::shared_ptr<StorageController> storageController_;

    /// \brief интерфейс контроллера внутреннего хранилища
    std::shared_ptr<TransportSubsystem> transportSubsystem_;
};

}
#endif