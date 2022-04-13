/// \file win_service_test.cpp тест работы службы windows

#include <gtest/gtest.h>

#include <Windows.h>
#include <memory>
#include <string>
#include <winsvc.h>


/// \brief
constexpr auto serviceName = "windows_service";

/// \brief
constexpr LPCWSTR serviceFullname= L"windows_service.exe";

constexpr auto MaxBufferSize = 2048;

/// \brief
TEST( ControlServiceTests, CreateTest )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE );
     ASSERT_NE( reinterpret_cast<uint64_t*> (serviceManager), nullptr );
     EXPECT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     auto buffer = std::make_unique<TCHAR[]>(MaxBufferSize);
     EXPECT_EQ( static_cast<uint64_t> (GetLastError()), 0 );
     GetCurrentDirectory( MaxBufferSize, buffer.get() );
     std::wstring servicePath =  (wchar_t*)buffer.get() ;
     servicePath += L"\\";
     servicePath += serviceFullname;
     std::string path = {servicePath.begin(), servicePath.end()};
     SC_HANDLE service = CreateServiceA
     (
          serviceManager,
          serviceName,
          serviceName,
          SERVICE_ALL_ACCESS,
          SERVICE_WIN32_OWN_PROCESS,
          SERVICE_DEMAND_START,
          SERVICE_ERROR_NORMAL,
          path.c_str(),
          NULL, NULL, NULL, "NT AUTHORITY\\NetworkService", NULL
     );

     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr );
     CloseServiceHandle( service );
     CloseServiceHandle( serviceManager );
}


/// \brief
TEST( ControlServiceTests, StartTest )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE );
     ASSERT_NE( reinterpret_cast<uint64_t*>(serviceManager), nullptr );
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     auto service = OpenService( serviceManager, serviceName, SERVICE_START );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr);
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     ASSERT_NE( static_cast<uint64_t>(StartServiceW( service, 0, NULL )),0 );
}

TEST( ControlServiceTests, StopService )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
     ASSERT_NE( reinterpret_cast<uint64_t*>(serviceManager), nullptr );

     auto service = OpenService( serviceManager, serviceName, SERVICE_STOP );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr );

     std::unique_ptr<SERVICE_STATUS> ServiceStatus( new SERVICE_STATUS );
     ASSERT_NE( ControlService( service, SERVICE_CONTROL_STOP, ServiceStatus.get() ),0 );
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     CloseServiceHandle( service );
     CloseServiceHandle( serviceManager );
}

TEST( ControlServiceTests, RemoveTest )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
     ASSERT_NE( reinterpret_cast<uint64_t*>(serviceManager), nullptr );

     auto service = OpenService( serviceManager, serviceName, DELETE );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr );

     ASSERT_NE( DeleteService( service ),0 );
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     CloseServiceHandle( service );
     CloseServiceHandle( serviceManager );
}