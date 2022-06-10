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

    *base_<<requests::SelectOptions, soci::into(enabled), soci::into(monitoring), soci::into(sending), soci::into(storage);

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

    *base_<<fmt::format(requests::SelectStringsCount, constants::OptionsTableName), soci::into(stringCount);

    if(!stringCount)
    {
        *base_<<requests::InsertOptions, soci::use(enabled), soci::use(monitoring)
        , soci::use(sending), soci::use(storage);
    }
    else
    {
         *base_<<requests::UpdateOptions, soci::use(enabled), soci::use(monitoring)
        , soci::use(sending), soci::use(storage);
    }
}

}