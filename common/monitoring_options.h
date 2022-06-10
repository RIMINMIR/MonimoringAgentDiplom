/// \file monitoring_options.h
/// \brief определение структуры настроек мониторинга

#pragma once
#ifndef COMMON_MONITORING_OPTIONS_H
#define COMMON_MONITORING_OPTIONS_H

#include <stdint.h>
#include <string>

namespace common
{

/// \file настройки мониторинга
struct MonitoringOptions
{
    /// \file мониторинг активирован
    bool MonitoringEnabled_;

    /// \file период мониторинга
    uint32_t MonitoringPeriod_;

    /// \file период отправки данных
    uint32_t SendingPeriod_;

    /// \file максимальный размер хранилища
    uint32_t MaxStorageSize_;

};

/// \file информация о подключении к серверу
struct ConnectionInfo
{
    /// \file имя хоста
    std::string Hostname_;

    /// \file пароль
    std::string Password_;
};

}

#endif