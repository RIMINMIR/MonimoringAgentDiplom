/// \file storage_test.cpp
/// \brief тест внутреннего хранилища

#include <internal_storage/database_controller.h>

#include <gtest/gtest.h>

/// \brief
TEST( StorageTests, DatabaseCreationTest )
{
   internalStorage::DatabaseController controller;
   ASSERT_NO_THROW( controller.CreateDatabase());
   ASSERT_TRUE(controller.CheckDatabaseIntegrity());
}
