/// \file transport_subsystem_impl.h
/// \brief определение реализации транспортной подсистемы

#pragma once
#ifndef CORE_TRANSPORT_SUBSYSTEM_IMPL_H
#define CORE_TRANSPORT_SUBSYSTEM_IMPL_H

#include <core/interfaces/transport_subsystem.h>

#include <common/monitoring_options.h>
#include <core/interfaces/storage_controller.h>
#include <core/interfaces/event_controller.h>

#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace core
{

class TransportSubsystemImpl : public TransportSubsystem
{
public:
    /// \brief конструктор контроллера событий
    TransportSubsystemImpl(std::shared_ptr<StorageController> storage);

    /// \brief деструктор контроллера событий
    ~TransportSubsystemImpl() override;

    /// \brief запуск контроллера событий
    void Run() override;

    /// \brief остановка контроллера событий
    void Stop() override;

    /// \brief установка настроек мониторинга
    void SetMonitoringOptions(const std::shared_ptr<common::MonitoringOptions> options) override;

    /// \brief отправка произошедшего события на сервер мониторинга
    /// \param event событие, отправка которого необходима
    virtual void SendMonitoringEvent(common::MonitoringEvent& event) override;

    /// \brief отправка собранных данных на сервера мониторинга
    /// \param data вектор с собранными метриками
    virtual void SendMonitoringData(std::vector<common::MonitoringData>& data) override;

private:
    /// \brief поток сбора данных
    void dataSending();

    /// \brief флаг работы потока
    bool isRunning_;

    /// \brief поток сбора данных
    std::thread sendingThread_;

    /// \brief структура настроек мониторинга
    std::shared_ptr<common::MonitoringOptions> options_;

    /// \brief контроллер внутреннего хранилища
    std::shared_ptr<StorageController> storage_;

    /// \brief переменная для синхронизации ожидания и выхода из потока по команде
    std::condition_variable threadActivated_;

    /// \brief Мьютекс для блокировки потока на ожидания
    std::mutex mutexLock_;

};

}

#endif

