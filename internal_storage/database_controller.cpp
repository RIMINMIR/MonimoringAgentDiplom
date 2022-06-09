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

void DatabaseController::CheckDatabaseIntegrity()
{

}

void DatabaseController::CreateDatabase()
{
    std::string request = fmt::format(requests::TableCreation, constants::MetricSettingsTableName, constants::MetricTableFields);
    *base_<<request;
}

void DatabaseController::CheckDatabaseSize()
{

}

}
