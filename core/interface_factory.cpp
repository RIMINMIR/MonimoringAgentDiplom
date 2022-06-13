/// \file interface_factory.cpp
/// \brief реализации фабрики интерфейсов ядра

#include "interface_factory.h"

#include <core/impl/core_impl.h>
#include <core/impl/event_controller_impl.h>
#include <core/impl/monitoring_subsystem_impl.h>
#include <core/impl/storage_controller_impl.h>
#include <core/impl/transport_subsystem_impl.h>

#include <core/impl/data_collectors/disk_space_collector.h>

#include <device_controller/data_receiver.h>

namespace factory
{

std::unique_ptr<core::Core> GetCore(common::CoreContent& content)
{
    auto core = std::make_unique<core::CoreImpl>(content);
    return std::move(core);
}

std::unique_ptr<core::EventController> GetEventController()
{
    auto controller = std::make_unique<core::EventControllerImpl>();
    return std::move(controller);
}

std::unique_ptr<core::MonitoringSubsystem> GetMonitoringSubsystem(std::shared_ptr<core::EventController> controller,
    core::CollectorList collectors, std::shared_ptr<core::StorageController> storage)
{
    auto subsystem = std::make_unique<core::MonitoringSubsystemImpl>(controller, collectors, storage);
    return std::move(subsystem);
}

std::unique_ptr<core::StorageController> GetStorageController()
{
    auto subsystem = std::make_unique<core::StorageControllerImpl>();
    return std::move(subsystem);
}

std::unique_ptr<core::TransportSubsystem> GetTransportSubsystem(std::shared_ptr<core::StorageController> storage)
{
    auto subsystem = std::make_unique<core::TransportSubsystemImpl>(storage);
    return std::move(subsystem);
}

core::CollectorList GetCollectorList(std::shared_ptr<common::metricOptions::MetricSettings> settings)
{
    auto list = std::make_shared< std::vector< std::shared_ptr< core::DataCollector > > >();
    auto dataDeceiver = std::make_shared<deviceController::DataReceiver>();
    std::shared_ptr< core::DataCollector > discSpaceCollector = std::make_shared<core::DiskSpaceCollector>(dataDeceiver, settings);
    list->push_back(discSpaceCollector);
    return list;
}

}
