/// \file database_controller_io.cpp
/// \brief реализация методов контроллера хранилища отвечающих за воод-вывод

#include "database_controller.h"
#include "sql_constants.h"
#include "sql_requests.h"

#include <fmt/core.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include <string>

namespace internalStorage
{

common::MonitoringOptions DatabaseController::LoadMonitoringOptions()
{
    int enabled = 0;
    int monitoring = 0;
    int sending = 0;
    int storage = 0;

    *base_ << requests::select::SelectOptions, soci::into(enabled), soci::into(monitoring), soci::into(sending), soci::into(storage);

    common::MonitoringOptions options = {static_cast<bool>(enabled), static_cast<uint32_t>(monitoring),
        static_cast<uint32_t>(sending), static_cast<uint32_t>(storage)};

    return options;
}

void DatabaseController::StoreMonitoringOptions(const common::MonitoringOptions& options)
{
    int enabled = static_cast<int>(options.MonitoringEnabled_);
    int monitoring = static_cast<int>(options.MonitoringPeriod_);
    int sending = static_cast<int>(options.SendingPeriod_);
    int storage = static_cast<int>(options.MaxStorageSize_);

    int stringCount = 0;

    *base_<<fmt::format(requests::select::SelectStringsCount, constants::OptionsTableName), soci::into(stringCount);

    if(!stringCount)
    {
        *base_ << requests::insert::InsertOptions, soci::use(enabled), soci::use(monitoring)
        , soci::use(sending), soci::use(storage);
    }
    else
    {
         *base_ << requests::update::UpdateOptions, soci::use(enabled), soci::use(monitoring)
        , soci::use(sending), soci::use(storage);
    }
}

void DatabaseController::StoreMetrics(const std::vector<common::MonitoringData>& data)
{
    std::vector<std::string> stringData = {};
    std::vector<int> date = {};
    std::vector<int> metricId = {};

    for(auto record:data)
    {
        stringData.push_back(record.stringData_);
        date.push_back(static_cast<int>(record.date));
        metricId.push_back(static_cast<int>(record.metrincName_));
    }

    *base_ << requests::insert::InsertMetrics, soci::use(stringData), soci::use(date), soci::use(metricId);

}

void DatabaseController::LoadMetrics(std::vector<common::MonitoringData>& data)
{
    std::vector<std::string> stringData = {};
    std::vector<int> date = {};
    std::vector<int> metricId = {};
    *base_ << requests::select::LoadMetrics, soci::into(stringData), soci::into(date), soci::into(metricId);
    for (int i =0; i < stringData.size(); i++)
    {
      common::MonitoringData tempData = {};
      tempData.stringData_ = stringData[i];
      tempData.date = date[i];
      tempData.metrincName_ = static_cast<common::collectingMetrics::MetricIds>(metricId[i]);

      data.push_back(tempData);
    }

    *base_ << fmt::format(requests::delete_::ClearTable, constants::MetricTableName);

}

}