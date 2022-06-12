/// \file database_controller.h
/// \brief контроллер управляющий внутренним хранилищем

#pragma once
#ifndef INTERNAL_STORAGE_DATABASE_CONTROLLER_H
#define INTERNAL_STORAGE_DATABASE_CONTROLLER_H

#include <common/monitoring_options.h>
#include <common/monitoring_data_structures.h>

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

    /// \brief проверка наличия настроек мониторинга в базе
    bool CheckMonitoringOptions();

    /// \brief проверка наличия настроек мониторинга в базе
    bool CheckMetricsSettings();

    /// \brief запрос размера базы данных
    uint64_t GetDatabaseSize();

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

    /// \brief настройки метрик
    /// \param settings настройки в строковом виде
    void StoreMetricSettings(const std::string& settings);

    /// \brief получение настроек метрик
    /// \param id идентификатор настроек метрик
    std::string GetMetricSettings();

    /// \brief удаление настроек метрик из хранилища
    /// \param id идентификатор компонента
    void DeleteMetricSettings();




private:

    std::shared_ptr<soci::session> base_;
};

}

#endif