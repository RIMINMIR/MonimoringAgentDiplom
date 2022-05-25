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
    if(sendingThread_.joinable())
    {
        sendingThread_.join();
    }
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
        std::this_thread::sleep_for(std::chrono::seconds(options_->SendingPeriod_));

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