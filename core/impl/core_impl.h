/// \file core_impl.h
/// \brief определение реализации ядра службы

#pragma once
#ifndef CORE_CORE_IMPL_H
#define CORE_CORE_IMPL_H

#include <core/interfaces/core.h>

#include <common/core_content.h>
#include <common/event_queue/event_queue.hpp>

namespace core
{

class CoreImpl : public Core
{
public:
    /// \brief конструктор
    /// \param content компоненты передаваемые в ядро
    CoreImpl(common::CoreContent& content);

    /// \brief деструктор
    ~CoreImpl() override;

    /// \brief запуск ядра службы
    void Run() override;

    /// \brief остановка ядра службы
    void Stop() override;

private:

};

}
#endif