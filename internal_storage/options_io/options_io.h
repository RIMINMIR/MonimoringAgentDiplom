/// \file options_io.h
/// \brief класс для загрузки и выгрузки опций из файла в хранилище

#pragma once
#ifndef INTERNAL_STORAGE_OPTIONS_IO_H
#define INTERNAL_STORAGE_OPTIONS_IO_H

#include <internal_storage/database_controller.h>

namespace internalStorage
{

/// \brief класс для получения данных о подсистемах через публичные методы
class OptionsIo
{
public:
    /// \brief конструктор
    /// \param storage контроллер внутреннего хранилища
    OptionsIo(std::shared_ptr<DatabaseController> storage);

    /// \brief чтение настроек из json файла
    /// \param path путь к json файлу
    void ReadOptions(const std::string& path);

    /// \brief запись настроек из хранилища в json файл
    /// \param path путь к json файлу
    void WriteOptions(const std::string& path);

    /// \brief установка в хранилище настроек по умолчанию
    /// \param path путь к json файлу
    void DefaultOptions();


private:

   std::shared_ptr<DatabaseController> storage_;

};

}

#endif