/// \file device_controller_strings.h
/// \brief строковые константы, необходимые для запроса данных о подсистемах

#pragma once
#ifndef DEVICE_CONTROLLER_DATA_REQUEST_STRINGS_H
#define DEVICE_CONTROLLER_DATA_REQUEST_STRINGS_H

namespace deviceController
{

/// \brief имена используемых wmi неймспейсов
namespace namespacesName
{
    constexpr auto Cimv2 = "ROOT\\CIMV2";

}

/// \brief имена классов из которых будут извлекаться wmi данные
namespace className
{
    /// \brief класс операционной системы
    constexpr auto OperatingSystem = "Win32_OperatingSystem";

    /// \brief класс логического диска
    constexpr auto LogicalDisk = "Win32_LogicalDisk";

    /// \brief класс информации о температуре
    constexpr auto ThermalZoneInformation = "Win32_PerfFormattedData_Counters_ThermalZoneInformation";
}


/// \brief имена полей классов данных
namespace fieldName
{
    /// \brief класс свободной виртуальной памяти
    constexpr auto FreeVirtualMemory = "FreeVirtualMemory";

    /// \brief класс свободной виртуальной памяти
    constexpr auto FreeDiskSpace = "FreeSpace";

    /// \brief класс свободной виртуальной памяти
    constexpr auto ProcessorTemperature = "Temperature";
}

}

#endif