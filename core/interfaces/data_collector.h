/// \file data_collector.h
/// \brief определение интерфейса сборщика данных

#pragma once
#ifndef CORE_DATA_COLLECTOR_H
#define CORE_DATA_COLLECTOR_H

#include <string>
#include <vector>
#include <memory>

namespace core
{

struct DataCollector
{
    /// \brief деструктор контроллера событий
    virtual ~DataCollector() = default;

    /// \brief получение данных мониторинга
    virtual std::string GetData() = 0;
};

using CollectorList = std::shared_ptr< std::vector<std::shared_ptr< core::DataCollector > > >;

}
#endif