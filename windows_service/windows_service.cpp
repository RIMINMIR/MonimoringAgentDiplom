/// \file windows_service.cpp
/// \brief служба windows

#include "windows_service.h"
#include <common/encoding_helper.h>

namespace win_service
{

/// \brief Название службы
LPWSTR ServiceName = {};

/// \brief Текущее состояние службы
SERVICE_STATUS_HANDLE StatusHandle = {};

/// \brief Статус службы
SERVICE_STATUS ServiceStatus = {};

/// \brief Основной поток агента маниторинга
HANDLE MainServiceThread = {};

std::unique_ptr<core::Core> Core = {};



int StartWindowsService(const std::wstring& serviceName, std::unique_ptr<core::Core> core)
{

    ServiceName = const_cast<LPWSTR>(serviceName.c_str());

    SERVICE_TABLE_ENTRYW ServiceTable[1];

    ServiceTable[0].lpServiceName = ServiceName;
    ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTIONW)ServiceMain;

    Core = std::move(core);

    if(!StartServiceCtrlDispatcherW(ServiceTable))
    {
        return GetLastError();
    }
    return 0;
}

void StopWindowsService()
{

}


void WINAPI ServiceMain(DWORD /*argc*/, LPWSTR* /*argv*/)
{
    StatusHandle = RegisterServiceCtrlHandlerW(ServiceName, ControlHandler);
    if (!StatusHandle)
    {
        return;
    }

    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP
        | SERVICE_ACCEPT_SHUTDOWN
        | SERVICE_ACCEPT_PAUSE_CONTINUE
        | SERVICE_USER_DEFINED_CONTROL;
    if(!UpdateStatus())
    {
        return;
    }

    Core->Run();

    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    if(!UpdateStatus())
    {
        return;
    }

    MainServiceThread = CreateThread(NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
}

DWORD WINAPI ServiceWorkerThread(LPVOID /*lpParam*/)
{
     ServiceStatus.dwCurrentState = SERVICE_RUNNING;
     if(!UpdateStatus())
     {
          ServiceStatus.dwCurrentState = SERVICE_STOPPED;
          ServiceStatus.dwControlsAccepted = 0;
          ServiceStatus.dwWin32ExitCode = GetLastError();
          ServiceStatus.dwCheckPoint = 1;
          UpdateStatus();
          return 1;
     }

     return ERROR_SUCCESS;
}

void WINAPI ControlHandler(DWORD request)
{
    switch (request)
    {
        case SERVICE_CONTROL_STOP:
            return OnServiceStop();

        case SERVICE_CONTROL_SHUTDOWN:
            return OnServiceStop();

        default:
            break;
    }
}

BOOL UpdateStatus()
{
     auto errorCode = SetServiceStatus(StatusHandle, &ServiceStatus);
     if(!errorCode)
     {
     }
     return errorCode;
}

void OnServiceStop()
{
    Core->Stop();
    CloseHandle(MainServiceThread);
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    UpdateStatus();
}

}