/// @file windows_service.h
/// @brief определение функций, используемых в службе windows

#pragma once
#ifndef ENTRY_POINTS_WINDOWS_SERVICE_H
#define ENTRY_POINTS_WINDOWS_SERVICE_H

#include "string"
namespace win_service
{

/// @brief создание службы windows
/// @param serviceName имя службы
/// @param path путь к службе
void CreateWindowsService(const std::string& serviceName, const std::string& path);

/// @brief запуск  службы windows
void StartWindowsService();

/// @brief остановка windows
void StopWindowsService();

}
#endif