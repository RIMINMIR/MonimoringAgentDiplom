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
    virtual void StoreOptions(const common::MonitoringOptions& options);

    /// \brief загрузка настроек мониторинга из хранилища
    /// \param options ссылка на загружаемые данные
    virtual void RequestOptions(common::MonitoringOptions& options);


    /// \brief сохранение данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    virtual void StoreMetrics(const common::MonitoringData& data);

    /// \brief сохранение вектора данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    virtual void StoreMetrics(const std::vector<common::MonitoringData>& data);

    /// \brief выгрузка вектора данных мониторинга из хранилища с послеюущей очисткой хранилища от них
    /// \param data ссылка на вектор загружаемых данных
    virtual void LoadMetrics(std::vector<common::MonitoringData>& data);

    /// \brief запрос вектора данных мониторинга из хранилища
    /// \param data ссылка на вектор загружаемых данных
    virtual void RequestMetrics(std::vector<common::MonitoringData>& data);

};

}
#endif