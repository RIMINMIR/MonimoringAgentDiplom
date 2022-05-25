/// \file core_content_h
/// \brief определение структуры с содержимым ядра

#pragma once
#ifndef COMMON_CORE_CONTENT_H
#define COMMON_CORE_CONTENT_H

#include <core/interfaces/event_controller.h>
#include <core/interfaces/monitoring_subsystem.h>
#include <core/interfaces/storage_controller.h>
#include <core/interfaces/transport_subsystem.h>

#include <memory>

namespace common
{

struct CoreContent
{
    /// \brief интерфейс контроллера событий
    std::shared_ptr<core::EventController> eventController_;

    /// \brief интерфейс подсистемы мониторинга
    std::shared_ptr<core::MonitoringSubsystem> monitoringSubsystem_;

    /// \brief интерфейс контроллера внутреннего хранилища
    std::shared_ptr<core::StorageController> storageController_;

    /// \brief интерфейс транспортной подсистемы
    std::shared_ptr<core::TransportSubsystem> transportSubsystem_;

};

}

#endif