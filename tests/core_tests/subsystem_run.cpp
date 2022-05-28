/// \file subsystem_run.cpp
/// \brief тесты запуска и остановки подсистем ядра

#include <core/interface_factory.h>

#include <gtest/gtest.h>

#include <thread>
#include <chrono>

/// \brief Тесты для проверки запуска и остановки контроллера событий
TEST( SubsystemRunTests, EventControllerRunTest )
{

auto eventController = factory::GetEventController();

eventController->Run();
std::this_thread::sleep_for(std::chrono::seconds(1));
eventController->Stop();

}

TEST( SubsystemRunTests, MonitoringSubsystemRunTest )
{

auto eventController = factory::GetEventController();

auto storageController = factory::GetStorageController();

auto collectors = factory::GetCollectorList();

auto monitoringSys = factory::GetMonitoringSubsystem(std::move(eventController), collectors, std::move(storageController));

auto monitoringOptions = std::make_shared<common::MonitoringOptions>();
monitoringOptions->MonitoringEnabled_ = true;
monitoringOptions->MonitoringPeriod_ = 30;
monitoringOptions->SendingPeriod_ = 30;
monitoringSys->SetMonitoringOptions(monitoringOptions);

monitoringSys->Run();
std::this_thread::sleep_for(std::chrono::seconds(1));
monitoringSys->Stop();

}