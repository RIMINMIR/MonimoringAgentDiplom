/// \file monitoring_subsystem_impl.cpp
/// \brief реализация подсистемы мониторинга

#include <core/impl/monitoring_subsystem_impl.h>

namespace core
{

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
    subsystemThread_.join();
}

void MonitoringSubsystemImpl::dataCollecting()
{

}

}