/// @file monitoring_agent.cpp
/// @brief точка входа в агент мониторинга

#include "stdint.h"

#include "windows_service.h"

#include <common/windows_service_data.h>

/// @brief точка входа в агент мониторинга
/// @param argc количество входных аргументов
/// @param argv входные аргументы
int main(uint32_t argc, char *argv[])
{
    auto dataCollectors = factory::GetCollectorList();
    common::CoreContent content = {};
    content.eventController_ = factory::GetEventController();
    content.storageController_ = factory::GetStorageController();
    content.monitoringSubsystem_ = factory::GetMonitoringSubsystem(content.eventController_, dataCollectors, content.storageController_);
    content.transportSubsystem_ = factory::GetTransportSubsystem(content.storageController_);

    auto corePtr = factory::GetCore(content);

    return win_service::StartWindowsService(common::windows_service_data::ServiceName, std::move(corePtr));
}