/// \file collecting_metrics.h
/// \brief определение собираемых метрик и их идентификаторов

#pragma once
#ifndef COMMON_COLLECTING_METRICS_H
#define COMMON_COLLECTING_METRICS_H

#include <string>

namespace common
{
namespace collectingMetrics
{

enum MetricIds
{
    ProcessorTemperature,
    FreeDiskSpace,
    FreeVirtualMemory,
    ProcessorTime
};

const std::string MetricNames[] = {"ProcessorTemperature", "FreeDiskSpace", "FreeVirtualMemory", "ProcessorTime"};

}
}

#endif