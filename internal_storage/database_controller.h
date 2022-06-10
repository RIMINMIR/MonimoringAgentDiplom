/// \file database_controller.h
/// \brief контроллер управляющий внутренним хранилищем

#pragma once
#ifndef INTERNAL_STORAGE_DATABASE_CONTROLLER_H
#define INTERNAL_STORAGE_DATABASE_CONTROLLER_H

#include <soci/soci.h>

#include <memory>

namespace internalStorage
{

/// \brief класс контроллера базы данных
class DatabaseController
{
public:
    /// \brief конструктор
    DatabaseController();

    /// \brief проверка целостности базы данных и её таблиц
    bool CheckDatabaseIntegrity();

    /// \brief создание базы данных и её таблиц
    void CreateDatabase();

    /// \brief проверка размера базы данных
    bool CheckDatabaseSize();

    /// \brief запрос размера базы данных
    uint64_t GetDatabaseSize();

private:

    std::unique_ptr<soci::session> base_;
};




/// \brief проверка целостности базы данных и её таблиц
/// \return true если все таблицы на месте иначе false
bool CheckDatabaseIntegrity();

/// \brief создание базы данных и её таблиц
void CreateDatabase();

/// \brief проверка размера базы данных
void CheckDatabaseSize();

}

#endif