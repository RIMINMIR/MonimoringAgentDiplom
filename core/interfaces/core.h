/// \file core.h
/// \brief определение интерфейса ядра службы

#pragma once
#ifndef CORE_CORE_H
#define CORE_CORE_H


namespace core
{

struct Core
{
    /// \brief запуск ядра службы
    virtual ~Core() = default;

    /// \brief запуск ядра службы
    virtual void Run() = 0;

    /// \brief остановка ядра службы
    virtual void Stop() = 0;
};

}
#endif