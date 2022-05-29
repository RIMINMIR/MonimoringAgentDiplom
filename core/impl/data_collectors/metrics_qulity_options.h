/// \file metrics_qulity_options
/// \brief структуры настроек показателей метрик
#pragma once
#ifndef CORE_METRICS_QUALITY_OPTIONS_H
#define CORE_METRICS_QUALITY_OPTIONS_H

#include <string>
#include <cstdint>

namespace core
{

/// \brief структуры настроек показателей метрик
namespace metricOptions
{
    /// \brief настройки показателей свободного места на диске
    struct FreeDiskSpace
    {
        std::string DiscName;

        uint64_t MinimalFreeSpace;
    };

    /// \brief настройки показателей оперативной памяти
    struct FreeVirtualMemory
    {
        uint64_t MinimalFreeMemory;
    };

     /// \brief настройки показателей оперативной памяти
    struct MaxProcessorTemperature
    {
        uint16_t MaxProcessorTemperature;
    };



}

}
#endif