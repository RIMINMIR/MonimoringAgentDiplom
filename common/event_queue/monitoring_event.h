/// \file monitoring_event.h
/// \brief определение обрабатываемых через единую очередь событий мониторинга

#pragma once
#ifndef COMMON_MONITORING_EVENT_H
#define COMMON_MONITORING_EVENT_H

#include <variant>

namespace common
{

struct TestEvent
{
    uint32_t testDigit_;
};

using MonitoringEvent = std::variant<TestEvent>;

}

#endif