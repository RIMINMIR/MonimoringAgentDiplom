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

std::vector<common::MonitoringData> DatabaseController::LoadMetrics()
{
    std::vector<common::MonitoringData> data = {};
    int storageSize = 0;
    *base_ << fmt::format(requests::select::SelectStringsCount, constants::MetricTableName), soci::into(storageSize);
    std::vector<std::string> stringData(storageSize);
    std::vector<int> date(storageSize);
    std::vector<int> metricId(storageSize);
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
    return data;
}


void DatabaseController::StoreConnection(const common::ConnectionInfo & conection)
{
    *base_ << requests::insert::InsertConnections, soci::use(conection.Hostname_), soci::use(conection.Password_);
}

std::vector<common::ConnectionInfo> DatabaseController::RequestConnections()
{
    std::vector<common::ConnectionInfo> data = {};
    int storageSize = 0;
    *base_ << fmt::format(requests::select::SelectStringsCount, constants::ServersTableName), soci::into(storageSize);
    std::vector<std::string> adreses(storageSize);
    std::vector<std::string> passes(storageSize);
    *base_ << requests::select::SelectServers, soci::into(adreses), soci::into(passes);
    for (int i =0; i < adreses.size(); i++)
    {
      common::ConnectionInfo tempData = {};
      tempData.Hostname_ = adreses[i];
      tempData.Password_ = passes[i];

      data.push_back(tempData);
    }
    return data;

}


void DatabaseController::StoreMetricSettings(const std::string& settings)
{
    int count = 0;
     *base_<<fmt::format(requests::select::SelectStringsCount, constants::MetricSettingsTableName), soci::into(count);
    if(!count)
    {
        *base_ << requests::insert::InsertMetricSettings, soci::use(settings);
    }
    else
    {
        *base_ << requests::update::UpdateMetricSettings, soci::use(settings);
    }
}

std::string DatabaseController::GetMetricSettings()
{
    std::string settings = {};
    *base_ << requests::select::SelectMetricSettings, soci::into(settings);
    return settings;
}

void DatabaseController::DeleteMetricSettings()
{
    *base_ << fmt::format(requests::delete_::ClearTable, constants::MetricSettingsTableName);
}

}