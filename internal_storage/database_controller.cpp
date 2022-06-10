/// \file database_controller.cpp
/// \brief реализация методов контроллера хранилища

#include "database_controller.h"
#include "sql_constants.h"
#include "sql_requests.h"

#include <fmt/core.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include <string>

namespace internalStorage
{

DatabaseController::DatabaseController()
    : base_{std::make_unique<soci::session>()}
{
    base_->open(soci::sqlite3, constants::StorageFileName);
}

bool DatabaseController::CheckDatabaseIntegrity()
{
    int integrityFlag = 0;
    std::string request = fmt::format(requests::TableNameCheck, constants::OptionsTableName);
    *base_<<request, soci::into(integrityFlag);
    if(integrityFlag == 0)
    {
        return false;
    }

    request = fmt::format(requests::TableNameCheck, constants::ComponentsTableName);
    *base_<<request, soci::into(integrityFlag);
    if(integrityFlag == 0)
    {
        return false;
    }

    request = fmt::format(requests::TableNameCheck, constants::ServersTableName);
    *base_<<request, soci::into(integrityFlag);
    if(integrityFlag == 0)
    {
        return false;
    }

    request = fmt::format(requests::TableNameCheck, constants::MetricTableName);
    *base_<<request, soci::into(integrityFlag);
    if(integrityFlag == 0)
    {
        return false;
    }

    request = fmt::format(requests::TableNameCheck, constants::MetricSettingsTableName);
    *base_<<request, soci::into(integrityFlag);
    if(integrityFlag == 0)
    {

    }
    return true;
}

void DatabaseController::CreateDatabase()
{
    std::string request = fmt::format(requests::TableCreation, constants::MetricTableName, constants::MetricTableFields);
    *base_<<request;
    request = fmt::format(requests::TableCreation, constants::OptionsTableName, constants::OptionsTableFields);
    *base_<<request;
    request = fmt::format(requests::TableCreation, constants::ComponentsTableName, constants::ComponentsTableFields);
    *base_<<request;
    request = fmt::format(requests::TableCreation, constants::MetricSettingsTableName, constants::MetricSettingsTableFields);
    *base_<<request;
    request = fmt::format(requests::TableCreation, constants::ServersTableName, constants::ServersTableFields);
    *base_<<request;
}

bool DatabaseController::CheckDatabaseSize()
{
    return true;
}

uint64_t DatabaseController::GetDatabaseSize()
{
    int size = 0;
    std::string request = requests::GetDatabaseSize;
    *base_<<request, soci::into(size);
    return size;
}

}
