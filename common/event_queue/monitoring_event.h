/// \file monitoring_event.h
/// \brief определение обрабатываемых через единую очередь событий мониторинга

#pragma once
#ifndef COMMON_MONITORING_EVENT_H
#define COMMON_MONITORING_EVENT_H

#include <variant>
#include <string>

namespace common
{

struct TestEvent
{
    uint32_t testDigit_;
};

struct DataCollectEvent
{
    std::string stringData_;
};


using MonitoringEvent = std::variant
<
    TestEvent,
    DataCollectEvent
>;

}

#endif