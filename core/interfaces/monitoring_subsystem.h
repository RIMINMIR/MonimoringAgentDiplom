/// \file monitoring_subsystem.h
/// \brief определение интерфейса доступа к подсистеме мониторинга

#pragma once
#ifndef CORE_MONITORUNG_SUBSYSTEM_H
#define CORE_MONITORUNG_SUBSYSTEM_H


namespace core
{

struct MonitoringSubsystem
{
    /// \brief деструктор подсистемы монитоинга
    virtual ~MonitoringSubsystem() = default;

    /// \brief запуск подсистемы монитоинга
    virtual void Run() = 0;

    /// \brief остановка подсистемы монитоинга
    virtual void Stop() = 0;
};

}
#endif