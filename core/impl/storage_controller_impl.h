/// \file storage_controller_impl.h
/// \brief определение реализации контроллера внутреннего хранилища

#pragma once
#ifndef CORE_STORAGE_CONTROLLER_IMPL
#define CORE_STORAGE_CONTROLLER_IMPL

#include <core/interfaces/storage_controller.h>

#include <common/event_queue/event_queue.hpp>
#include <common/event_queue/monitoring_event.h>

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

    /// \brief сохранение настроек мониторинга в хранилище
    /// \param options ссылка на помещаемые данные
    void StoreOptions(const common::MonitoringOptions& options) override;

    /// \brief загрузка настроек мониторинга из хранилища
    /// \param options ссылка на загружаемые данные
    void RequestOptions(common::MonitoringOptions& options) override;


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

};

}
#endif