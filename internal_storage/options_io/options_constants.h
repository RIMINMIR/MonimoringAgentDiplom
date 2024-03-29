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

/// \brief максимальный размер хранилища
constexpr auto StorageSize = u8"MaxStorageSize";


/// \brief свободная оперативная память
constexpr auto FreeVirtualMemory = u8"FreeVirtualMemory";

/// \brief свободное место на дискке
constexpr auto FreeDiskSpace = u8"FreeDiskSpace";

/// \brief загрузка процессора
constexpr auto ProcessorTime = u8"ProcessorTime";

/// \brief температура процессора
constexpr auto ProcessorTemperature = u8"ProcessorTemperature";

/// \brief температура процессора
constexpr auto Adress = u8"ServerAdress";

/// \brief температура процессора
constexpr auto Password = u8"Password";

constexpr auto Servers = u8"Servers";

constexpr auto DefaultMetricsSettings = u8"\
    {\
        \"ProcessorTemperature\": 354,\
        \"ProcessorTime\": 85,\
         \"FreeDiskSpace\": {\"D\":107374182400, \"C\": 10737418240}, \"FreeVirtualMemory\": 6442450943\
    }";

}
}

#endif