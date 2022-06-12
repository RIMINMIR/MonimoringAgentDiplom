/// \file options_io.cpp
/// \brief тест модуля загрузки опций

#include <internal_storage/database_controller.h>
#include <common/monitoring_data_structures.h>
#include <internal_storage/options_io/options_io.h>
#include <internal_storage/options_io/options_constants.h>

#include <nlohmann/json.hpp>

#include <gtest/gtest.h>
#include <fstream>

    const std::string filepath = u8"D:/lessons/options.json";
     const std::string filepathOut = u8"D:/lessons/ururu.json";
     const std::string SettingsForParse  = u8"\
    {\
        \"ProcessorTemperature\": 354,\
        \"ProcessorTime\": 85,\
         \"FreeDiskSpace\": {\"D\":107374182400, \"C\": 10737418240}, \"FreeVirtualMemory\": 6442450943\
    }";
/// \brief проверка создания базы и таблиц
TEST( OptionsIoTests, ReadTest )
{
    auto controller = std::make_shared<internalStorage::DatabaseController>();
    internalStorage::OptionsIo io(controller);
    ASSERT_NO_THROW(io.ReadOptions(filepath));
}

/// \brief проверка создания базы и таблиц
TEST( OptionsIoTests, WriteTest )
{
    auto controller = std::make_shared<internalStorage::DatabaseController>();
    internalStorage::OptionsIo io(controller);
    ASSERT_NO_THROW(io.WriteOptions(filepathOut));
}

using namespace internalStorage;
/// \brief проверка создания базы и таблиц
TEST( OptionsIoTests, ValueDiffTest )
{

    auto controller = std::make_shared<internalStorage::DatabaseController>();
    internalStorage::OptionsIo io(controller);

    std::ifstream f(filepathOut);
    ASSERT_TRUE(f.is_open());
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
    auto storSet = controller->GetMetricSettings();
    auto storOpt = controller->LoadMonitoringOptions();

    ASSERT_EQ(storSet, metricSettings);
    ASSERT_EQ(storOpt.MaxStorageSize_, monOptions.MaxStorageSize_);
    ASSERT_EQ(storOpt.MonitoringEnabled_, monOptions.MonitoringEnabled_);
    ASSERT_EQ(storOpt.MonitoringPeriod_, monOptions.MonitoringPeriod_);
    ASSERT_EQ(storOpt.SendingPeriod_, monOptions.SendingPeriod_);
}

/// \brief проверка создания базы и таблиц
TEST( OptionsIoTests, ParseSettingsTest )
{
    auto controller = std::make_shared<internalStorage::DatabaseController>();
    internalStorage::OptionsIo io(controller);
    common::metricOptions::MetricSettings parsedSet = {};
    ASSERT_NO_THROW(parsedSet = io.parseSettings(SettingsForParse));
    ASSERT_EQ(parsedSet.freeMemory.MinimalFreeMemory, 6442450943);
    ASSERT_EQ(parsedSet.maxTemperature.MaxProcessorTemperature,354);
    ASSERT_EQ(parsedSet.processorTime.MaxProcessorTime, 85);
}