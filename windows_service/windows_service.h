/// @file windows_service.h
/// @brief определение функций, используемых в службе windows

#pragma once
#ifndef ENTRY_POINTS_WINDOWS_SERVICE_H
#define ENTRY_POINTS_WINDOWS_SERVICE_H

#include <core/interface_factory.h>

#include "Windows.h"
#include "winsvc.h"

#include "string"

namespace win_service
{

/// @brief создание службы windows
/// @param serviceName имя службы
/// @param path путь к службе
void CreateWindowsService(const std::string& serviceName, const std::string& path);

/// @brief запуск  службы windows
int StartWindowsService(const std::wstring& serviceName, std::unique_ptr<core::Core> core);

/// @brief основная функция, работающая после запуска службы
void WINAPI ServiceMain(DWORD /*argc*/, LPWSTR* /*argv*/);

/// @brief основной поток работы службы
DWORD WINAPI ServiceWorkerThread(LPVOID /*lpParam*/);

/// @brief обработчик команд службе
void WINAPI ControlHandler(DWORD request);

/// @brief обновление статуса службы
BOOL UpdateStatus();

/// @brief обработка остановки службы
void OnServiceStop();

}
#endif