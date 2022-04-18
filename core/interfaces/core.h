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
    virtual ~Core();

    /// \brief запуск ядра службы
    virtual void Run();

    /// \brief остановка ядра службы
    virtual void Stop();
};

}
#endif