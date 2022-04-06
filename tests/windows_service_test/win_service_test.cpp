/// \brief

#include <entry_point/win/service/service_common.h>

#include <gtest/gtest.h>

#include <Windows.h>
#include <memory>
#include <string>
#include <winsvc.h>

using namespace infotecs;

/// \brief
constexpr LPCWSTR serviceName = L"nvsAgent";

/// \brief
constexpr LPCWSTR serviceFullname= L"NvsAgent.exe";


/// \brief
TEST( ControlServiceTests, CreateTest )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE );
     ASSERT_NE( reinterpret_cast<uint64_t*> (serviceManager), nullptr );
     EXPECT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     std::unique_ptr<TCHAR> buffer( new TCHAR[nvs_agent::service::MaxBufferSize] );
     EXPECT_EQ( static_cast<uint64_t> (GetLastError()), 0 );
     GetCurrentDirectory( nvs_agent::service::MaxBufferSize, buffer.get() );
     std::wstring servicePath( buffer.get() );
     servicePath += L"\\";
     servicePath += serviceFullname;
     SC_HANDLE service = CreateService
     (
          serviceManager,
          serviceName,
          serviceName,
          SERVICE_ALL_ACCESS,
          SERVICE_WIN32_OWN_PROCESS,
          SERVICE_DEMAND_START,
          SERVICE_ERROR_NORMAL,
          servicePath.c_str(),
          NULL, NULL, NULL, L"NT AUTHORITY\\NetworkService", NULL
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

     ASSERT_NE( static_cast<uint64_t>(StartService( service, 0, NULL )),0 );
}


/// \brief
TEST( ControlServiceTests, PauseService )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
     ASSERT_NE( reinterpret_cast<uint64_t*>(serviceManager), nullptr );

     auto service = OpenService( serviceManager, serviceName, SERVICE_PAUSE_CONTINUE );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr );
     std::unique_ptr<SERVICE_STATUS> ServiceStatus( new SERVICE_STATUS );
     ASSERT_NE( static_cast<uint64_t>(ControlService( service, SERVICE_CONTROL_PAUSE, ServiceStatus.get() )),0 );
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     CloseServiceHandle( service );
     CloseServiceHandle( serviceManager );
}


/// \brief
TEST( ControlServiceTests, ContinueService )
{
     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
     ASSERT_NE( reinterpret_cast<uint64_t*>(serviceManager), nullptr );

     auto service = OpenService( serviceManager, serviceName, SERVICE_PAUSE_CONTINUE );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr );

     std::unique_ptr<SERVICE_STATUS> ServiceStatus( new SERVICE_STATUS );
     ASSERT_NE( (ControlService( service, SERVICE_CONTROL_CONTINUE, ServiceStatus.get() )),0 );
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     CloseServiceHandle( service );
     CloseServiceHandle( serviceManager );
}


TEST( ControlServiceTests, getinfoService )
{
     auto sharedMemory = OpenFileMapping( FILE_MAP_READ | FILE_MAP_WRITE, false, nvs_agent::service::SharedMemoryName );
     ASSERT_NE( reinterpret_cast<uint64_t*>(sharedMemory), nullptr );

     auto data = ( nvs_agent::service::ServiceComandInfo* )MapViewOfFile( sharedMemory, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0 );
     ASSERT_NE( data, nullptr );

     data->processStatus.store( nvs_agent::service::Status::MemoryFree );

     while ( data->processStatus.load() != nvs_agent::service::Status::MemoryFree )
     {
          continue;
     }
     data->processStatus.store( nvs_agent::service::Status::OccupiedByApp );

     auto serviceManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
     ASSERT_NE( reinterpret_cast<uint64_t*>( serviceManager ), nullptr );

     auto service = OpenService( serviceManager, serviceName, SERVICE_USER_DEFINED_CONTROL | SERVICE_QUERY_STATUS );
     ASSERT_NE( reinterpret_cast<uint64_t*>(service), nullptr );

     std::unique_ptr<SERVICE_STATUS> ServiceStatus( new SERVICE_STATUS );

     data->processStatus.store( nvs_agent::service::Status::OccupiedByService );
     ASSERT_NE( ControlService( service, SERVICE_GET_INFO, ServiceStatus.get() ),0 );
     ASSERT_EQ( static_cast<uint64_t> (GetLastError()), 0 );

     while ( data->processStatus.load() != nvs_agent::service::Status::OccupiedByApp )
     {
     }

     int servisStateCode = data->comandCode;
     data->processStatus.store( nvs_agent::service::MemoryFree );

     CloseServiceHandle( service );
     CloseServiceHandle( serviceManager );

     ASSERT_EQ( servisStateCode, nvs_agent::service::GetInfoCode );

     UnmapViewOfFile( data );
     CloseHandle( sharedMemory );
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