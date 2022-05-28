/// \file monitoring_data_structures.h
/// \brief определение структуры данных мониторинга

#pragma once
#ifndef COMMON_MONITORING_DATA_STRUCTURES_H
#define COMMON_MONITORING_DATA_STRUCTURES_H

#include <common/collecting_metrics.h>

#include <string>

namespace common
{

struct MonitoringData
{
    /// \file собранные данные в строковом виде
    std::string stringData_;

    /// \file идентификатор собранной метрики
    common::collectingMetrics::MetricIds metrincName_;

    /// \file дата сбора данных в виде числа
    uint64_t date;

};

}

#endif