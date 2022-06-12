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

common::metricOptions::MetricSettings OptionsIo::parseSettings(const std::string& settingsString)
{
    common::metricOptions::MetricSettings resultSettings = {};
    auto settingsObj = nlohmann::json::parse(settingsString);
    resultSettings.freeMemory.MinimalFreeMemory = settingsObj[constants::FreeVirtualMemory].get<uint64_t>();
    resultSettings.maxTemperature.MaxProcessorTemperature = settingsObj[constants::ProcessorTemperature].get<uint16_t>();
    resultSettings.processorTime.MaxProcessorTime = settingsObj[constants::ProcessorTime].get<uint16_t>();
    auto tempObject = settingsObj[constants::FreeDiskSpace].get<nlohmann::json::object_t>();
    for(auto& space:tempObject)
    {
        resultSettings.freeSpace.push_back(common::metricOptions::FreeDiskSpace{space.first, space.second});
    }
    return resultSettings;
}

void OptionsIo::DefaultOptions()
{
    common::MonitoringOptions options =  {true, 10, 180, 52428800 };
    storage_->StoreMonitoringOptions(options);
    storage_->StoreMetricSettings(constants::DefaultMetricsSettings);
}

void OptionsIo::MemorizeOptionSet(
        std::shared_ptr<common::MonitoringOptions> monitoringOptions,
        std::shared_ptr<common::metricOptions::MetricSettings> metricSettings,
        const std::string& path)
{
    if(!(storage_->CheckMetricsSettings() && storage_->CheckMonitoringOptions() ))
    {
        try
        {
            ReadOptions(path);

        }
        catch(const std::exception&)
        {
            DefaultOptions();
        }

    }

    *monitoringOptions = storage_->LoadMonitoringOptions();
    auto settingsString = storage_->GetMetricSettings();
    *metricSettings =  parseSettings(settingsString);

}

}