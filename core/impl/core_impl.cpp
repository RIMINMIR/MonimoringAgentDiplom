/// \file core_impl.cpp
/// \brief реализация методов ядра службы

#include "core_impl.h"

namespace core
{

CoreImpl::CoreImpl(common::CoreContent& content)
    : monitoringSubsystem_{content.monitoringSubsystem_}
    , eventController_{content.eventController_}
    , storageController_{content.storageController_}
    , transportSubsystem_{content.transportSubsystem_}
    , monitoringOptions_{std::make_shared<common::MonitoringOptions>()}
    , metricSettings_{ std::make_shared < common::metricOptions::MetricSettings>() }
{

}

CoreImpl::~CoreImpl()
{
    Stop();
}

void CoreImpl::Run()
{
    storageController_->InitOptions(monitoringOptions_, metricSettings_);
    monitoringSubsystem_->SetMonitoringOptions(monitoringOptions_);
    transportSubsystem_->SetMonitoringOptions(monitoringOptions_);

    monitoringSubsystem_->Run();
    eventController_->Run();
    transportSubsystem_->Run();
}

void CoreImpl::Stop()
{
    monitoringSubsystem_->Stop();
    eventController_->Stop();
    transportSubsystem_->Stop();
}

}