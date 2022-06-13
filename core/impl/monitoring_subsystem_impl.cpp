/// \file monitoring_subsystem_impl.cpp
/// \brief реализация подсистемы мониторинга

#include <core/impl/monitoring_subsystem_impl.h>
#include <common/event_queue/monitoring_event.h>

#include <chrono>
#include <ctime>



namespace core
{

MonitoringSubsystemImpl::MonitoringSubsystemImpl(std::shared_ptr<EventController> controller, CollectorList collectors,
    std::shared_ptr<core::StorageController> storage)
: events_{controller}
, storage_{storage}
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
}

void MonitoringSubsystemImpl::Stop()
{
    isRunning_ = false;
    threadActivated_.notify_one();
    if(collectingThread_.joinable())
    {
        collectingThread_.join();
    }
}

void MonitoringSubsystemImpl::SetMonitoringOptions(const std::shared_ptr<common::MonitoringOptions> options)
{
    options_ = options;
}

void MonitoringSubsystemImpl::dataCollecting()
{
    while(isRunning_)
    {
        std::unique_lock lk(mutexLock_);
        threadActivated_.wait_for(lk, std::chrono::seconds(options_->MonitoringPeriod_));

        if(!isRunning_)
        {
            return;
        }
        std::vector<common::MonitoringData> dataVector = {};
        /*for (auto collector : *collectors_)
        {
            deviceState::paramStates subsystemState = deviceState::Unknown;
            auto subsystemData = collector->GetData(subsystemState);
            if(subsystemState == deviceState::NotNormal)
            {
                common::NotNormalMetricEvent anomalyMetric = {subsystemData};
                common::MonitoringEvent queueEvent = {anomalyMetric};
                events_->PutEvent(queueEvent);
            }
            else if (subsystemState == deviceState::Ok)
            {
               common::MonitoringData dataStruct = {};
               dataStruct.stringData_ = subsystemData;
               dataStruct.metricName_ = collector->GetMetricName();
               dataStruct.date = time(NULL);
               /// \todo доделать установку текущей даты и сбор имени метрики

                dataVector.push_back(dataStruct);
            }


        }*/

        storage_->StoreMetrics(dataVector);
    }

}

}