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

}
}

#endif