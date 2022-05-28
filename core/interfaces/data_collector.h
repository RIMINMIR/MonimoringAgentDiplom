/// \file data_collector.h
/// \brief определение интерфейса сборщика данных

#pragma once
#ifndef CORE_DATA_COLLECTOR_H
#define CORE_DATA_COLLECTOR_H

#include <common/collecting_metrics.h>

#include <string>
#include <vector>
#include <memory>

namespace core
{

namespace deviceState
{

enum paramStates
{
    Unknown = 0,
    Ok = 1,
    NotNormal = 2
};

}

struct DataCollector
{
    /// \brief деструктор контроллера событий
    virtual ~DataCollector() = default;

    /// \brief получение данных мониторинга
    virtual std::string GetData(deviceState::paramStates& systemState) = 0;

    /// \brief получение названия метрики
    /// \return идентификатор запрашиваемой метрики
    virtual common::collectingMetrics::MetricIds GetMetricName() = 0;
};

using CollectorList = std::shared_ptr< std::vector<std::shared_ptr< core::DataCollector > > >;

}
#endif