/// \file disk_space_collector.h
/// \brief реализация сборщика данных для сбора данных о жестком диске

#pragma once
#ifndef CORE_DISK_SPACE_COLLECTOR_H
#define CORE_DISK_SPACE_COLLECTOR_H

#include <core/interfaces/data_collector.h>
#include "metrics_qulity_options.h"

#include <device_controller/data_receiver.h>

namespace core
{

class DiskSpaceCollector : public DataCollector
{
public:

    /// \todo реализовать сборщик настроек и их централизованное хранение в ядре
    /// \brief конструктор
    /// \param data указатель на wmi сборщик данных
    DiskSpaceCollector(std::shared_ptr<deviceController::DataReceiver> data, std::shared_ptr<std::vector<metricOptions::FreeDiskSpace>> diskOptions);

    /// \brief деструктор контроллера событий
    ~DiskSpaceCollector() override;

    /// \brief получение данных мониторинга
    std::string GetData(deviceState::paramStates& systemState) override;

    /// \brief получение названия метрики
    /// \return идентификатор запрашиваемой метрики
    common::collectingMetrics::MetricIds GetMetricName() override;

private:

    /// \brief проверить данные на соответствие критическим значениям
    /// \param data вектор строковых данных для проверки
    bool check(std::shared_ptr<std::vector<std::string>> data);

    /// \brief вектор настроек для каждого диска
    std::shared_ptr<std::vector<metricOptions::FreeDiskSpace>> diskOptions_;

    // \brief сборщик данных через wmi
    std::shared_ptr<deviceController::DataReceiver> data_;

};

}
#endif