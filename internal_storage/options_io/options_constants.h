/// \file options_constants.h
/// \brief константы для парсингаг опций

#pragma once
#ifndef INTERNAL_STORAGE_OPTIONS_CONSTANTS_H
#define INTERNAL_STORAGE_OPTIONS_CONSTANTS_H


namespace internalStorage
{
namespace constants
{

/// \brief имя поля с настройками мониторинга
constexpr auto MonitoringOptions = u8"MonitoringOptions";

/// \brief имя поля с настройками метрик
constexpr auto MetricSettings = u8"MetricSettings";

/// \brief имя поля с настройками метрик
constexpr auto MonitoringEnabled = u8"MonitoringEnabled";

/// \brief имя поля с настройками метрик
constexpr auto MonitoringPeriod = u8"MonitoringPeriod";

/// \brief имя поля с настройками метрик
constexpr auto SendingPeriod = u8"SendingPeriod";

constexpr auto StorageSize = u8"MaxStorageSize";

}
}

#endif