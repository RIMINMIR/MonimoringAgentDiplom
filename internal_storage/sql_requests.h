/// \file sql_requests.h
/// \brief sql запросы в строковом формате

#pragma once
#ifndef INTERNAL_STORAGE_SQL_REQUESTS_H
#define INTERNAL_STORAGE_SQL_REQUESTS_H

namespace internalStorage
{

namespace requests
{

/// \brief sql запрос создания таблицы
constexpr auto TableCreation = u8"CREATE TABLE IF NOT EXISTS '{0}'({1}); ";

constexpr auto TableNameCheck = u8"SELECT count(*) FROM sqlite_master WHERE type='table' AND name='{0}';";

/// \brief Получение текущего размера БД
constexpr auto GetDatabaseSize = u8"SELECT page_count * page_size AS size FROM pragma_page_count(), pragma_page_size()";

}

}

#endif