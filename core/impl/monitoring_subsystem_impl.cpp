/// \file monitoring_subsystem_impl.cpp
/// \brief реализация подсистемы мониторинга

#include <core/impl/monitoring_subsystem_impl.h>
#include <common/event_queue/monitoring_event.h>

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
    collectingThread_ = std::thread(&MonitoringSubsystemImpl::dataCollecting, this);
    sendingThread_ = std::thread(&MonitoringSubsystemImpl::dataSending, this);
}

void MonitoringSubsystemImpl::Stop()
{
    isRunning_ = false;
    if(collectingThread_.joinable())
    {
        collectingThread_.join();
    }
    if(sendingThread_.joinable())
    {
        sendingThread_.join();
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

        for(auto collector:*collectors_)
        {
            auto subsystemData = collector->GetData();
            common::DataCollectEvent dataEvent = {};
            dataEvent.stringData_ = subsystemData;
            common::MonitoringEvent queueEvent = {dataEvent};

            events_->PutEvent(queueEvent);
        }
    }

}

void MonitoringSubsystemImpl::dataSending()
{
    while(isRunning_)
    {
        std::this_thread::sleep_for(std::chrono::seconds(options_->SendingPeriod_));

        if(!isRunning_)
        {
            return;
        }

    }

}

}