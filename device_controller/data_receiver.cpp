/// \file data_receiver.cpp
/// \brief реализация методов контроллера, позволяющего работать с wmi

#include "data_receiver.h"
#include "data_request_strings.h"

namespace deviceController
{

DataReceiver::DataReceiver()
    :wmi_{std::make_unique<WmiController>()}
{

}

std::shared_ptr<std::vector<std::string>> DataReceiver::GetFreeVirtualMemory()
{
    auto data = wmi_->Request(namespacesName::Cimv2, className::OperatingSystem, fieldName::FreeVirtualMemory);
    return data;
}

std::shared_ptr<std::vector<std::string>> DataReceiver::GetDriveSpace()
{
    std::vector<std::string> arguments = {fieldName::Name, fieldName::FreeDiskSpace};
    auto data = wmi_->Request(namespacesName::Cimv2, className::LogicalDisk, arguments);
    return data;
}

std::shared_ptr<std::vector<std::string>> DataReceiver::GetProcessorTemperature()
{
    auto data = wmi_->Request(namespacesName::Cimv2, className::ThermalZoneInformation, fieldName::ProcessorTemperature);
    return data;
}

std::shared_ptr<std::vector<std::string>> DataReceiver::GetPercentProcessorTime()
{
    auto data = wmi_->Request(namespacesName::Cimv2, className::ProcessorInformation, fieldName::PercentProcessorTime);
    return data;
}

}