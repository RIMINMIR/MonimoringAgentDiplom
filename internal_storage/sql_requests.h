/// \file sql_requests.h
/// \brief sql запросы в строковом формате

#pragma once
#ifndef INTERNAL_STORAGE_SQL_REQUESTS_H
#define INTERNAL_STORAGE_SQL_REQUESTS_H

namespace internalStorage
{

namespace requests
{

namespace create
{

/// \brief sql запрос создания таблицы
constexpr auto TableCreation = u8"CREATE TABLE IF NOT EXISTS '{0}'({1}); ";

}

namespace select
{
/// \brief проверка наличия таблицы в базе
constexpr auto TableNameCheck = u8"SELECT count(*) FROM sqlite_master WHERE type='table' AND name='{0}';";

/// \brief Получение текущего размера БД
constexpr auto GetDatabaseSize = u8"SELECT page_count * page_size AS size FROM pragma_page_count(), pragma_page_size()";

/// \brief запрос опций
constexpr auto SelectOptions = u8"SELECT MonitoringEnabled, MonitoringPeriod, SendingPeriod, MaxDatabaseSize from MonitoringOptions;";

/// \brief запрос количества записей в таблице
constexpr auto SelectStringsCount = u8"SELECT count(*) FROM {0}";

/// \brief проверка наличия записи в таблице
constexpr auto StringCheck = u8"SELECT count(*) FROM {0} WHERE Id = {1}";

/// \brief запрос метрик из таблицы
constexpr auto LoadMetrics = u8"SELECT StringData, Date, ComponentId from Metrics;";

/// \brief запрос метрик из таблицы
constexpr auto SelectServers = u8"SELECT ServerAdress, Password from Servers;";

/// \brief запрос настроек метрик из таблицы
constexpr auto SelectMetricSettings = u8"SELECT Settings from MetricSettings;";
}

namespace insert
{

/// \brief установка опций
constexpr auto InsertOptions = u8"INSERT INTO MonitoringOptions(MonitoringEnabled, MonitoringPeriod, SendingPeriod, MaxDatabaseSize)\
 values(:enabled, :monitoring, :sending, :size)";

/// \brief установка метрик
constexpr auto InsertMetrics = u8"INSERT INTO Metrics(StringData, Date, ComponentId)\
 values(:data, :date, :componentId)";

/// \brief установка метрик
constexpr auto InsertConnections = u8"INSERT INTO Servers(ServerAdress, Password)\
 values(:adr, :pas)";

/// \brief установка настроек метрик
constexpr auto InsertMetricSettings = u8"INSERT INTO  MetricSettings(Settings) values(:set);";

}

namespace update
{
/// \brief обновление существующих опций
constexpr auto UpdateOptions = u8"UPDATE MonitoringOptions SET MonitoringEnabled = :enabled, MonitoringPeriod = :monitoring,\
 SendingPeriod = :sending, MaxDatabaseSize = :size";

 /// \brief обновление существующих настроек метрик
constexpr auto UpdateMetricSettings = u8"UPDATE MetricSettings SET  Settings = :name";
}

namespace delete_
{

/// \brief обновление существующих опций
constexpr auto ClearTable = u8"delete from {0}";

/// \brief обновление существующих опций
constexpr auto DeleteServer = u8"DELETE FROM Servers WHERE ServerAdress = {0}";

/// \brief обновление существующих опций
constexpr auto RotateMetrics = u8"DELETE FROM Metrics WHERE Id IN (SELECT Id FROM Metrics ORDER BY id ASC LIMIT :num)";
}





}

}

#endif