/// \file interface_factory.h
/// \brief определение фабрики интерфейсов ядра

#pragma once
#ifndef CORE_INTERFACE_FACTORY_H
#define CORE_INTERFACE_FACTORY_H

#include <core/interfaces/core.h>

#include <common/core_content.h>

#include <memory>

namespace factory
{

std::unique_ptr<core::Core> GetCore(common::CoreContent& content);

}
#endif