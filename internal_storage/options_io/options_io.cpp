/// \file options_io.cpp
/// \brief реализация чтения записи и генерации настроек

#include "options_io.h"
#include "options_constants.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <stdexcept>


namespace internalStorage
{
OptionsIo::OptionsIo(std::shared_ptr<DatabaseController> storage)
    : storage_{storage}
{

}

void OptionsIo::ReadOptions(const std::string& path)
{
    /// быстрое чтение из файла
    std::ifstream f(path);
    if(!f.is_open())
    {
        throw std::runtime_error(u8"file not opened");
    }
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string options(size, ' ');
    f.seekg(0);
    f.read(&options[0], size);
    f.close();

    nlohmann::json jsonFile = nlohmann::json::parse(options);
    auto metricSettings = jsonFile[constants::MetricSettings].dump();
    common::MonitoringOptions monOptions  = {
        static_cast<bool>(jsonFile[constants::MonitoringOptions][constants::MonitoringEnabled].get<int>()),
        static_cast<uint32_t>(jsonFile[constants::MonitoringOptions][constants::MonitoringPeriod].get<int>()),
        static_cast<uint32_t>(jsonFile[constants::MonitoringOptions][constants::SendingPeriod].get<int>()),
        static_cast<uint32_t>(jsonFile[constants::MonitoringOptions][constants::StorageSize].get<int>())
        };
    storage_->StoreMetricSettings(metricSettings);
    storage_->StoreMonitoringOptions(monOptions);
}

void OptionsIo::WriteOptions(const std::string& path)
{
    std::ofstream f(path);
    auto metricSettings = storage_->GetMetricSettings();
    auto monitoringOptions = storage_->LoadMonitoringOptions();
    nlohmann::json jsonFile = {};
    jsonFile[constants::MonitoringOptions] = {
        {constants::MonitoringEnabled, monitoringOptions.MonitoringEnabled_},
        {constants::MonitoringPeriod, monitoringOptions.MonitoringPeriod_},
        {constants::SendingPeriod, monitoringOptions.SendingPeriod_},
        {constants::StorageSize, monitoringOptions.MaxStorageSize_}
    };
    auto settingsObj = nlohmann::json::parse(metricSettings);
    jsonFile[constants::MetricSettings] = settingsObj;
    auto fileRes = jsonFile.dump(1);
    f<<fileRes;
    f.close();

}
}