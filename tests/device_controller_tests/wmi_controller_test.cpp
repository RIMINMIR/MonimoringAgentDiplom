/// \file wmi_controller_test.cpp
/// \brief Тесты для проверки контроллера wmi

#include <device_controller/wmi_controller.h>

#include <gtest/gtest.h>

/// \brief Тесты для проверки контроллера wmi. запрос значения, проверка что поолучен результат, проверка что он не пустой
TEST( WmiControllerTests, DataRequest )
{
    deviceController::WmiController wmi;

    auto data = wmi.Request("ROOT\\CIMV2", "Win32_OperatingSystem", "Name");

    ASSERT_GT(data->size(), 0);

    auto result = data->back();

    ASSERT_NE(result.c_str(), "");

}