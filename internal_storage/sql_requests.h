/// \file sql_requests.h
/// \brief sql запросы в строковом формате

#pragma once
#ifndef INTERNAL_STORAGE_SQL_REQUESTS_H
#define INTERNAL_STORAGE_SQL_REQUESTS_H

namespace internalStorage
{

namespace requests
{

/// \brief sql запрос создания таблицы
constexpr auto TableCreation = u8"CREATE TABLE IF NOT EXISTS '{0}'({1}); ";

constexpr auto TableNameCheck = u8"SELECT count(*) FROM sqlite_master WHERE type='table' AND name='{0}';";

/// \brief Получение текущего размера БД
constexpr auto GetDatabaseSize = u8"SELECT page_count * page_size AS size FROM pragma_page_count(), pragma_page_size()";

/// \brief запрос опций
constexpr auto SelectOptions = u8"SELECT MonitoringEnabled, MonitoringPeriod, SendingPeriod, MaxDatabaseSize from MonitoringOptions;";

/// \brief установка опций
constexpr auto InsertOptions = u8"INSERT INTO MonitoringOptions(MonitoringEnabled, MonitoringPeriod, SendingPeriod, MaxDatabaseSize)\
 values(:enabled, :monitoring, :sending, :size)";

/// \brief запрос количества записей в таблице
constexpr auto SelectStringsCount = u8"SELECT count(*) FROM {0}";

/// \brief
constexpr auto UpdateOptions = u8"UPDATE MonitoringOptions SET MonitoringEnabled = :enabled, MonitoringPeriod = :monitoring,\
 SendingPeriod = :sending, MaxDatabaseSize = :size";

}

}

#endif