/// \file storage_test.cpp
/// \brief тест внутреннего хранилища

#include <internal_storage/database_controller.h>

#include <gtest/gtest.h>

/// \brief проверка создания базы и таблиц
TEST( StorageTests, DatabaseCreationTest )
{
   internalStorage::DatabaseController controller;
   ASSERT_NO_THROW( controller.CreateDatabase());
   ASSERT_TRUE(controller.CheckDatabaseIntegrity());
   ASSERT_NE(controller.GetDatabaseSize(), 0);
}

/// \brief проверка создания базы и таблиц
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
}