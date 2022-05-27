/// \file storage_controller.h
/// \brief определение интерфейса контроллера хранилища

#pragma once
#ifndef CORE_MONITORUNG_STORAGE_CONTROLLER
#define CORE_MONITORUNG_STORAGE_CONTROLLER

#include <common/monitoring_data_structures.h>
#include <common/monitoring_options.h>

#include <vector>

namespace core
{

struct StorageController
{
    /// \brief деструктор подсистемы монитоинга
    virtual ~StorageController() = default;

    /// \brief сохранение настроек мониторинга в хранилище
    /// \param options ссылка на помещаемые данные
    virtual void StoreOptions(const common::MonitoringOptions& options) = 0;

    /// \brief загрузка настроек мониторинга из хранилища
    /// \param options ссылка на загружаемые данные
    virtual void RequestOptions(common::MonitoringOptions& options) = 0;


    /// \brief сохранение адреса сервера мониторинга
    /// \param connection ссылка на данные о сервере мониторинга
    virtual void StoreConnection(const common::ConnectionInfo & conection) = 0;

    /// \brief загрузка данных о серверах мониторинга
    /// \param connections ссылка на загружаемые данные
    virtual void RequestConnections(std::vector<common::ConnectionInfo>& connections) = 0;

     /// \brief удаление данных о сервере мониторинга из хранилища
    /// \param connection ссылка на удаляемые даднные
    virtual void RemoveConnection(const common::ConnectionInfo & conection) = 0;


    /// \brief сохранение данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    virtual void StoreMetrics(const common::MonitoringData& data) = 0;

    /// \brief сохранение вектора данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    virtual void StoreMetrics(const std::vector<common::MonitoringData>& data) = 0;

    /// \brief выгрузка вектора данных мониторинга из хранилища с послеюущей очисткой хранилища от них
    /// \param data ссылка на вектор загружаемых данных
    virtual void LoadMetrics(std::vector<common::MonitoringData>& data) = 0;

    /// \brief запрос вектора данных мониторинга из хранилища
    /// \param data ссылка на вектор загружаемых данных
    virtual void RequestMetrics(std::vector<common::MonitoringData>& data) = 0;

};

}
#endif