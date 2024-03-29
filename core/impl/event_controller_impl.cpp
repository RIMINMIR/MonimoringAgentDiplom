/// \file event_controller_impl.h
/// \brief реализация методов контроллера событий

#include "event_controller_impl.h"

namespace core
{

EventControllerImpl::EventControllerImpl()
{

}

EventControllerImpl::~EventControllerImpl()
{
    Stop();
}

void EventControllerImpl::Run()
{
    isRunning_ = true;
    processEventThread_ = std::thread(&EventControllerImpl::processEvent, this);
}

void EventControllerImpl::Stop()
{
    isRunning_ = false;
    if (processEventThread_.joinable())
    {
        processEventThread_.join();
    }
}

void EventControllerImpl::PutEvent(common::MonitoringEvent& event)
{
    queue_->Push(event);
}

void EventControllerImpl::processEvent()
{

}

}