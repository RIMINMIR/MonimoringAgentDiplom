/// @file monitoring_agent.cpp
/// @brief точка входа в агент мониторинга

#include "stdint.h"

#include "windows_service.h"

#include <common/windows_service_data.h>

/// @brief точка входа в агент мониторинга
/// @param argc количество входных аргументов
/// @param argv входные аргументы
int main(uint32_t argc, char *argv[])
{
    return win_service::StartWindowsService(common::windows_service_data::ServiceName);
}