/// \file database_io.h
/// \brief интерфейс для ввода вывода данных в хранилище

#pragma once
#ifndef INTERNAL_STORAGE_DATABASE_IO_H
#define INTERNAL_STORAGE_DATABASE_IO_H

#include <common/monitoring_options.h>
#include <common/monitoring_data_structures.h>

#include <soci/soci.h>

#include <memory>

namespace internalStorage
{

/// \brief класс контроллера базы данных
class DatabaseIo
{
public:
    /// \brief конструктор
    DatabaseIo();

    /// \brief запрос настроек мониторинга
    /// \return структура с настройками из хранилища
    common::MonitoringOptions LoadMonitoringOptions();

    /// \brief загруска настроек мониторинга
    /// \return структура с настройками из хранилища
    void StoreMonitoringOptions(const common::MonitoringOptions& options);

    /// \brief сохранение вектора данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    void StoreMetrics(const std::vector<common::MonitoringData>& data);

    /// \brief выгрузка вектора данных мониторинга из хранилища с послеюущей очисткой хранилища от них
    /// \param data ссылка на вектор загружаемых данных
    std::vector<common::MonitoringData> LoadMetrics();

    /// \brief сохранение адреса сервера мониторинга
    /// \param connection ссылка на данные о сервере мониторинга
    void StoreConnection(const common::ConnectionInfo & conection);

    /// \brief загрузка данных о серверах мониторинга
    /// \param connections ссылка на загружаемые данные
    std::vector<common::ConnectionInfo> RequestConnections();

    /// \brief загрузка данных о компонентах
    /// \param componentName имя компонента
    /// \param id идентификатор компонента
    void StoreComponents(const int& id, const std::string& componentName);

    /// \brief удаление компонента из хранилища
    /// \param id идентификатор компонента
    void DeleteComponents(const int& id);

    /// \brief настройки метрик
    /// \param settings настройки в строковом виде
    /// \param id идентификатор компонента
    void StoreMetricSettings(const int& id, const std::string& settings);

    /// \brief удаление настроек метрик из хранилища
    /// \param id идентификатор компонента
    void DeleteMetricSettings(const int& id);




private:

    std::shared_ptr<soci::session> base_;
};

}

#endif