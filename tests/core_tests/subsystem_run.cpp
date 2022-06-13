/// \file subsystem_run.cpp
/// \brief тесты запуска и остановки подсистем ядра

#include <core/interface_factory.h>

#include <gtest/gtest.h>

#include <thread>
#include <chrono>

/// \brief Время между запуском и остановкой подсистемы в милисекундах
constexpr auto WaitTime = 200;

/// \brief Тесты для проверки запуска и остановки контроллера событий
TEST( SubsystemRunTests, EventControllerRunTest )
{
    auto eventController = factory::GetEventController();

    eventController->Run();
    std::this_thread::sleep_for(std::chrono::microseconds(WaitTime));
    eventController->Stop();
}

TEST( SubsystemRunTests, MonitoringSubsystemRunTest )
{
    auto eventController = factory::GetEventController();

    auto storageController = factory::GetStorageController();
    auto settings = std::make_shared<common::metricOptions::MetricSettings>();
    auto collectors = factory::GetCollectorList(settings );

    auto monitoringSys = factory::GetMonitoringSubsystem(std::move(eventController), collectors, std::move(storageController));

    auto monitoringOptions = std::make_shared<common::MonitoringOptions>();
    monitoringOptions->MonitoringEnabled_ = true;
    monitoringOptions->MonitoringPeriod_ = 30;
    monitoringOptions->SendingPeriod_ = 30;
    monitoringSys->SetMonitoringOptions(monitoringOptions);

    monitoringSys->Run();
    std::this_thread::sleep_for(std::chrono::microseconds(WaitTime));
    monitoringSys->Stop();
}

TEST( SubsystemRunTests, TransportSubsystemRunTest )
{
    auto storageController = factory::GetStorageController();
    auto transportSubsystem = factory::GetTransportSubsystem(std::move(storageController));
    auto monitoringOptions = std::make_shared<common::MonitoringOptions>();
    monitoringOptions->MonitoringEnabled_ = true;
    monitoringOptions->MonitoringPeriod_ = 30;
    monitoringOptions->SendingPeriod_ = 30;
    transportSubsystem->SetMonitoringOptions(monitoringOptions);

    transportSubsystem->Run();
    std::this_thread::sleep_for(std::chrono::microseconds(WaitTime));
    transportSubsystem->Stop();
}

TEST( SubsystemRunTests, CoreRunTest )
{
    auto settings = std::make_shared<common::metricOptions::MetricSettings>();
    auto options = std::make_shared<common::MonitoringOptions>();
    auto dataCollectors = factory::GetCollectorList(settings );
    common::CoreContent content = {};
    content.monitoringOptions_ = options;
    content.metricSettings_ = settings;
    content.eventController_ = factory::GetEventController();
    content.storageController_ = factory::GetStorageController();
    content.monitoringSubsystem_ = factory::GetMonitoringSubsystem(content.eventController_, dataCollectors, content.storageController_);
    content.transportSubsystem_ = factory::GetTransportSubsystem(content.storageController_);

    std::shared_ptr<core::Core> corePtr = factory::GetCore(content);

    corePtr->Run();
    std::this_thread::sleep_for(std::chrono::microseconds(WaitTime));
    corePtr->Stop();
}