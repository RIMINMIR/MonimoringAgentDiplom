/// \file storage_test.cpp
/// \brief тест внутреннего хранилища

#include <internal_storage/database_controller.h>

#include <gtest/gtest.h>

/// \brief
TEST( StorageTests, DatabaseCreationTest )
{
   internalStorage::DatabaseController controller;
   controller.CreateDatabase();
}
