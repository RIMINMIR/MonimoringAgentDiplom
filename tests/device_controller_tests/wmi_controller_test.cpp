/// \file wmi_controller_test.cpp
/// \brief Тесты для проверки контроллера wmi

#include <device_controller/wmi_controller.h>

#include <gtest/gtest.h>

/// \brief Тесты для проверки контроллера wmi. запрос значения, проверка что поолучен результат, проверка что он не пустой
TEST( WmiControllerTests, OSDataRequest )
{
    deviceController::WmiController wmi;

    auto data = wmi.Request("ROOT\\CIMV2", "Win32_OperatingSystem", "Name");

    ASSERT_GT(data->size(), 0);

    auto result = data->back();

    ASSERT_NE(result.c_str(), "");

}

/// \brief Тесты для проверки контроллера wmi. запрос значения, проверка что поолучен результат, проверка что он не пустой
TEST( WmiControllerTests, TemperatureDataRequest )
{
    deviceController::WmiController wmi;

    auto data = wmi.Request("ROOT\\CIMV2", "Win32_PerfFormattedData_Counters_ThermalZoneInformation", "Temperature");

    ASSERT_GT(data->size(), 0);

    auto result = data->back();

    ASSERT_NE(result.c_str(), "");

}

/// \brief Тесты для проверки контроллера wmi. запрос значения, проверка что поолучен результат, проверка что он не пустой
TEST( WmiControllerTests, FreeDriveSpaceTest )
{
    deviceController::WmiController wmi;

    auto data = wmi.Request("ROOT\\CIMV2", "Win32_LogicalDisk", "FreeSpace");

    ASSERT_GT(data->size(), 0);

    auto result = data->back();

    ASSERT_NE(result.c_str(), "");

}

/// \brief Тесты для проверки контроллера wmi. запрос значения, проверка что поолучен результат, проверка что он не пустой
TEST( WmiControllerTests, FreeVirtualMemoryTest )
{
    deviceController::WmiController wmi;

    auto data = wmi.Request("ROOT\\CIMV2", "Win32_OperatingSystem", "FreeVirtualMemory");

    ASSERT_GT(data->size(), 0);

    auto result = data->back();

    ASSERT_NE(result.c_str(), "");
}

/// \brief Тесты для проверки контроллера wmi. запрос вектора значений и проверка корректности результата
TEST( WmiControllerTests, ProcessorTimePercentTest )
{
    deviceController::WmiController wmi;

    std::vector<std::string> arguments = {"Name", "PercentProcessorTime"};

    auto data = wmi.Request("ROOT\\CIMV2", "Win32_PerfFormattedData_Counters_ProcessorInformation", arguments);

    ASSERT_GT(data->size(), 0);

    auto result = data->back();

    ASSERT_NE(result.c_str(), "");
}



