/// \file monitoring_subsystem_impl.cpp
/// \brief реализация подсистемы мониторинга

#include <core/impl/monitoring_subsystem_impl.h>

#include <chrono>

namespace core
{

MonitoringSubsystemImpl::MonitoringSubsystemImpl(std::shared_ptr<EventController> controller, CollectorList collectors)
: events_{controller}
{

}

MonitoringSubsystemImpl::~MonitoringSubsystemImpl()
{
    Stop();
}

void MonitoringSubsystemImpl::Run()
{
    isRunning_ = true;
    subsystemThread_ = std::thread(&MonitoringSubsystemImpl::dataCollecting, this);
}

void MonitoringSubsystemImpl::Stop()
{
    isRunning_ = false;
    if(subsystemThread_.joinable())
    {
        subsystemThread_.join();
    }
}

void MonitoringSubsystemImpl::dataCollecting()
{
    while(isRunning_)
    {
        std::this_thread::sleep_for(std::chrono::seconds(options_->MonitoringPeriod_));

        if(!isRunning_)
        {
            return;
        }

    }

}

}