/// \file interface_factory.cpp
/// \brief реализации фабрики интерфейсов ядра

#include "interface_factory.h"

#include <core/impl/core_impl.h>

namespace factory
{

std::unique_ptr<core::Core> GetCore(common::CoreContent& content)
{
    auto core = std::make_unique<core::CoreImpl>(content);
    return std::move(core);
}

}
