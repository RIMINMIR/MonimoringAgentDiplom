/// \file storage_test.cpp
/// \brief тест внутреннего хранилища

#include <internal_storage/database_controller.h>
#include <common/monitoring_data_structures.h>

#include <gtest/gtest.h>

/// \brief проверка создания базы и таблиц
TEST( StorageTests, DatabaseCreationTest )
{
   internalStorage::DatabaseController controller;
   ASSERT_NO_THROW( controller.CreateDatabase());
   ASSERT_TRUE(controller.CheckDatabaseIntegrity());
   ASSERT_NE(controller.GetDatabaseSize(), 0);
}

/// \brief проверка загрузки и выгрузки настроек
TEST( StorageTests, StoreOptionsTest )
{
   internalStorage::DatabaseController controller;
   common::MonitoringOptions options = {true, 5, 15, 9999};
   controller.StoreMonitoringOptions(options);
   auto loadedOptions = controller.LoadMonitoringOptions();
   ASSERT_EQ(options.MonitoringEnabled_, loadedOptions.MonitoringEnabled_);
   ASSERT_EQ(options.MonitoringPeriod_, loadedOptions.MonitoringPeriod_);
   ASSERT_EQ(options.SendingPeriod_, loadedOptions.SendingPeriod_);
   ASSERT_EQ(options.MaxStorageSize_, loadedOptions.MaxStorageSize_);
   options = {false, 10, 20, 21000};
   controller.StoreMonitoringOptions(options);
   loadedOptions = controller.LoadMonitoringOptions();
   ASSERT_EQ(options.MonitoringEnabled_, loadedOptions.MonitoringEnabled_);
   ASSERT_EQ(options.MonitoringPeriod_, loadedOptions.MonitoringPeriod_);
   ASSERT_EQ(options.SendingPeriod_, loadedOptions.SendingPeriod_);
   ASSERT_EQ(options.MaxStorageSize_, loadedOptions.MaxStorageSize_);
}

/// \brief проверка загрузки и выгрузки метрик
TEST( StorageTests, StoreMetricsTest )
{
   internalStorage::DatabaseController controller;
   common::MonitoringData metric = {};
   metric.date = 50;
   metric.metrincName_ = common::collectingMetrics::FreeDiskSpace;
   metric.stringData_ = u8"320";
   std::vector<common::MonitoringData> metrics = {metric};
   controller.StoreMetrics(metrics);
   auto results = controller.LoadMetrics();
   ASSERT_EQ(results[0].date, metric.date);
   ASSERT_EQ(results[0].metrincName_, metric.metrincName_);
   ASSERT_EQ(results[0].stringData_, metric.stringData_);

}

/// \brief проверка загрузки и выгрузки метрик
TEST( StorageTests, StoreServers )
{
   internalStorage::DatabaseController controller;
   common::ConnectionInfo server = {};
   server.Hostname_ = u8"testname";
   server.Password_ = u8"testPass";
   controller.StoreConnection(server);
   auto results = controller.RequestConnections();

   ASSERT_EQ(results[0].Hostname_, server.Hostname_);
   ASSERT_EQ(results[0].Password_, server.Password_);


}