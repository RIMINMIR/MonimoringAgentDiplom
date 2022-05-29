/// \file data_receiver.h
/// \brief класс для получения данных о подсистемах через публичные методы

#pragma once
#ifndef DEVICE_CONTROLLER_DATA_RECEIVER_H
#define DEVICE_CONTROLLER_DATA_RECEIVER_H

#include "wmi_controller.h"

namespace deviceController
{

/// \brief класс для получения данных о подсистемах через публичные методы
class DataReceiver
{
public:
    /// \brief конструктор
    DataReceiver();

    /// \brief деструктор
    ~DataReceiver() = default;

    /// \brief запрос свободного места на диске
    /// \return вектор со строковыми значениями свободного места на дисках
    std::shared_ptr<std::vector<std::string>> GetDriveSpace();

    /// \brief запрос размера свободной виртуальной памяти
    /// \return вектор со строковым значением свободной виртуальной памяти
    std::shared_ptr<std::vector<std::string>> GetFreeVirtualMemory();

    /// \brief запрос температуры процессора
    /// \return вектор со строковым значением температуры процессора
    std::shared_ptr<std::vector<std::string>> GetProcessorTemperature();

    /// \brief запрос нагрузки на процессор в процентах
    /// \return вектор со строковыми значениями нагрузки на процессор и его ядра
    std::shared_ptr<std::vector<std::string>> GetPercentProcessorTime();

private:

   std::unique_ptr<WmiController> wmi_;

};

}

#endif