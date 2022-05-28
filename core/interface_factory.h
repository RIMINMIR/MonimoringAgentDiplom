/// \file interface_factory.h
/// \brief определение фабрики интерфейсов ядра

#pragma once
#ifndef CORE_INTERFACE_FACTORY_H
#define CORE_INTERFACE_FACTORY_H

#include <core/interfaces/core.h>
#include <core/interfaces/monitoring_subsystem.h>
#include <core/interfaces/data_collector.h>
#include <core/interfaces/event_controller.h>
#include <core/interfaces/storage_controller.h>
#include <core/interfaces/transport_subsystem.h>

#include <common/core_content.h>

#include <memory>
#include <vector>

namespace factory
{

/// \brief получение интерфейса ядра
/// \param content компоненты ядра
std::unique_ptr<core::Core> GetCore(common::CoreContent& content);

/// \brief получение сборщика данных
std::unique_ptr<core::DataCollector> GetDataCollector();

/// \brief получение обработчика событий
std::unique_ptr<core::EventController> GetEventController();

/// \brief получение подсистемы мониторинга
/// \param collectors вектор с указаелями на сборщики данных
std::unique_ptr<core::MonitoringSubsystem> GetMonitoringSubsystem(std::shared_ptr<core::EventController> controller,
    core::CollectorList collectors, std::shared_ptr<core::StorageController> storage);

/// \brief получение контроллера внутреннего хранилища
std::unique_ptr<core::StorageController> GetStorageController();

/// \brief получение контроллера внутреннего хранилища
std::unique_ptr<core::TransportSubsystem> GetTransportSubsystem(std::shared_ptr<core::StorageController> storage);

/// \brief получение вектора сборщиков данных
core::CollectorList GetCollectorList();

}
#endif