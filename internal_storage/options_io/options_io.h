/// \file options_io.h
/// \brief класс для загрузки и выгрузки опций из файла в хранилище

#pragma once
#ifndef INTERNAL_STORAGE_OPTIONS_IO_H
#define INTERNAL_STORAGE_OPTIONS_IO_H

#include <internal_storage/database_controller.h>

#include <common/metrics_qulity_options.h>
#include <common/monitoring_options.h>

namespace internalStorage
{

/// \brief класс для получения данных о подсистемах через публичные методы
class OptionsIo
{
public:

    /// \brief конструктор
    /// \param storage контроллер внутреннего хранилища
    OptionsIo(std::shared_ptr<DatabaseController> storage);

    /// \brief загрузка настроек в память
    /// \param path путь к файлу с настройками
    void MemorizeOptionSet(
        std::shared_ptr<common::MonitoringOptions> monitoringOptions,
        std::shared_ptr<common::metricOptions::MetricSettings> metricSettings,
        const std::string& path);

    /// \brief чтение настроек из json файла
    /// \param path путь к json файлу
    void ReadOptions(const std::string& path);

    /// \brief запись настроек из хранилища в json файл
    /// \param path путь к json файлу
    void WriteOptions(const std::string& path);

    /// \brief установка в хранилище настроек по умолчанию
    void DefaultOptions();

    /// \brief парсинк настроек мониторинга
    /// \param optionsString строка с настройками в json
    common::metricOptions::MetricSettings parseSettings(const std::string& settingsString);

private:

    std::shared_ptr<DatabaseController> storage_;
};

}

#endif