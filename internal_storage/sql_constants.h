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
constexpr auto SettingsTableName = u8"MonitoringSettings";

/// \brief поля таблицы настроек мониторинга
constexpr auto SettingsTableFields = "MonitoringEnabled INTEGER, MonitoringPeriod INTEGER, SendingPeriod INTEGER";

/// \brief имя таблицы серверов
constexpr auto ServersTableName = u8"Servers";

/// \brief поля таблицы серверов
constexpr auto ServersTableFields = "Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ServerAdress TEXT, Password TEXT";

/// \brief имя таблицы настроек метрик
constexpr auto MetricSettingsTableName = u8"MetricSettings";

/// \brief поля таблицы серверов
constexpr auto MetricSettingsTableFields = "ComponentId INTEGER PRIMARY KEY NOT NULL, Settings TEXT";

/// \brief имя таблицы компонентов
constexpr auto ComponentsTableName = u8"Components";

/// \brief поля таблицы серверов
constexpr auto ComponentsTableFields = "ComponentId INTEGER PRIMARY KEY NOT NULL, ComponentName TEXT";

}

}

#endif