/// \file transport_subsystem_impl.cpp
/// \brief  реализация транспортной подсистемы

#include "transport_subsystem_impl.h"

namespace core
{

TransportSubsystemImpl::TransportSubsystemImpl(std::shared_ptr<StorageController> storage)
    : storage_{storage}
{

}

TransportSubsystemImpl::~TransportSubsystemImpl()
{

}

void TransportSubsystemImpl::Run()
{
    isRunning_ = true;
    sendingThread_ = std::thread(&TransportSubsystemImpl::dataSending, this);
}

void TransportSubsystemImpl::Stop()
{

    isRunning_ = false;
    threadActivated_.notify_one();
    if(sendingThread_.joinable())
    {
        sendingThread_.join();
    }
}

void TransportSubsystemImpl::SetMonitoringOptions(const std::shared_ptr<common::MonitoringOptions> options)
{
    options_ = options;
}

void TransportSubsystemImpl::SendMonitoringEvent(common::MonitoringEvent& event)
{

}

void TransportSubsystemImpl::SendMonitoringData(std::vector<common::MonitoringData>& data)
{

}

void TransportSubsystemImpl::dataSending()
{

    while(isRunning_)
    {

        std::unique_lock lk(mutexLock_);
        threadActivated_.wait_for(lk, std::chrono::seconds(options_->MonitoringPeriod_));

        if(!isRunning_)
        {
            return;
        }

        std::vector<common::MonitoringData> data = {};
        storage_->LoadMetrics(data);
        if(data.size() > 0)
        {
            SendMonitoringData(data);
        }

    }

}

}