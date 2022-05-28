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
{
    auto monitoringOptions = std::make_shared<common::MonitoringOptions>();
    monitoringOptions->MonitoringEnabled_ = true;
    monitoringOptions->MonitoringPeriod_ = 30;
    monitoringOptions->SendingPeriod_ = 30;

    monitoringSubsystem_->SetMonitoringOptions(monitoringOptions);
    transportSubsystem_->SetMonitoringOptions(monitoringOptions);
}

CoreImpl::~CoreImpl()
{
    Stop();
}

void CoreImpl::Run()
{
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