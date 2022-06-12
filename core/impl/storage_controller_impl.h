/// \file storage_controller_impl.h
/// \brief определение реализации контроллера внутреннего хранилища

#pragma once
#ifndef CORE_STORAGE_CONTROLLER_IMPL_H
#define CORE_STORAGE_CONTROLLER_IMPL_H

#include <core/interfaces/storage_controller.h>

#include <common/event_queue/event_queue.hpp>
#include <common/event_queue/monitoring_event.h>

#include <internal_storage/database_controller.h>
#include <internal_storage/options_io/options_io.h>

#include <memory>
#include <atomic>
#include <thread>

namespace core
{

class StorageControllerImpl : public StorageController
{
public:
    /// \brief конструктор контроллера событий
    StorageControllerImpl();

    /// \brief деструктор контроллера событий
    ~StorageControllerImpl() override;

    /// \brief инициализация настроек из внутреннего хранилища, переданного файла или дефолтных
    /// \param monitoringOptions настройки мониторинга
    /// \param metricSettings параметры метрик
    void InitOptions(
        std::shared_ptr<common::MonitoringOptions> monitoringOptions,
        std::shared_ptr<common::metricOptions::MetricSettings> metricSettings,
        const std::string& path = u8"D:/lessons/options.json") override;

    /// \brief сохранение настроек мониторинга в хранилище
    /// \param options ссылка на помещаемые данные
    void StoreOptions(const common::MonitoringOptions& options) override;

    /// \brief загрузка настроек мониторинга из хранилища
    /// \param options ссылка на загружаемые данные
    void RequestOptions(common::MonitoringOptions& options) override;


    /// \brief сохранение адреса сервера мониторинга
    /// \param connection ссылка на данные о сервере мониторинга
    void StoreConnection(const common::ConnectionInfo & conection) override;

    /// \brief загрузка данных о серверах мониторинга
    /// \param connections ссылка на загружаемые данные
    void RequestConnections(std::vector<common::ConnectionInfo>& connections) override;

    /// \brief удаление данных о сервере мониторинга из хранилища
    /// \param connection ссылка на удаляемые даднные
    void RemoveConnection(const common::ConnectionInfo & conection) override;


    /// \brief сохранение данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    void StoreMetrics(const common::MonitoringData& data) override;

    /// \brief сохранение вектора данных мониторинга в хранилище
    /// \param data ссылка на помещаемые данные
    void StoreMetrics(const std::vector<common::MonitoringData>& data) override;

    /// \brief выгрузка вектора данных мониторинга из хранилища с послеюущей очисткой хранилища от них
    /// \param data ссылка на вектор загружаемых данных
    void LoadMetrics(std::vector<common::MonitoringData>& data) override;

    /// \brief запрос вектора данных мониторинга из хранилища
    /// \param data ссылка на вектор загружаемых данных
    void RequestMetrics(std::vector<common::MonitoringData>& data) override;

private:

    std::shared_ptr<internalStorage::DatabaseController> database_;

    std::shared_ptr<internalStorage::OptionsIo> optionLoader_;

};

}
#endif