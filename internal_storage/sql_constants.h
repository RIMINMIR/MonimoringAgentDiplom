/// \file sql_constants.h
/// \brief константы во внутреннем хранилище

#pragma once
#ifndef INTERNAL_STORAGE_SQL_CONSTANTS_H
#define INTERNAL_STORAGE_SQL_CONSTANTS_H

namespace internalStorage
{

namespace constants
{

/// \brief имя файла базы
constexpr auto StorageFileName = u8"internal_storage.db";

/// \brief имя таблицы метрик
constexpr auto MetricTableName = u8"Metrics";

/// \brief поля таблицы метрик
constexpr auto MetricTableFields = u8"Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, StringData TEXT, Date INTEGER, ComponentId INTEGER";

/// \brief имя таблицы настроек мониторинга
constexpr auto OptionsTableName = u8"MonitoringOptions";

/// \brief поля таблицы настроек мониторинга
constexpr auto OptionsTableFields = "MonitoringEnabled INTEGER, MonitoringPeriod INTEGER, SendingPeriod INTEGER, MaxDatabaseSize INTEGER";

/// \brief имя таблицы серверов
constexpr auto ServersTableName = u8"Servers";

/// \brief поля таблицы серверов
constexpr auto ServersTableFields = "Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ServerAdress TEXT, Password TEXT";

/// \brief имя таблицы настроек метрик
constexpr auto MetricSettingsTableName = u8"MetricSettings";

/// \brief поля таблицы серверов
constexpr auto MetricSettingsTableFields = "Settings TEXT";

}

}

#endif