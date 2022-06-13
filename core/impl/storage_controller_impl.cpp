/// \file storage_controller_impl.cpp
/// \brief  реализация контроллера внутреннего хранилища

#include "storage_controller_impl.h"

namespace core
{

StorageControllerImpl::StorageControllerImpl()
    : database_{std::make_shared<internalStorage::DatabaseController>()}
{
    optionLoader_ = std::make_shared<internalStorage::OptionsIo>(database_);
    if(!database_->CheckDatabaseIntegrity())
    {
        database_->CreateDatabase();
    }
}

StorageControllerImpl::~StorageControllerImpl()
{

}

void StorageControllerImpl::InitOptions(
        std::shared_ptr<common::MonitoringOptions> monitoringOptions,
        std::shared_ptr<common::metricOptions::MetricSettings> metricSettings,
        const std::string& path)
{
    optionLoader_->MemorizeOptionSet(monitoringOptions, metricSettings, path);
}

void StorageControllerImpl::StoreOptions(const common::MonitoringOptions& options)
{
    database_->StoreMonitoringOptions(options);
}

void StorageControllerImpl::RequestOptions(common::MonitoringOptions& options)
{
    options = database_->LoadMonitoringOptions();
}

void StorageControllerImpl::StoreConnection(const common::ConnectionInfo & conection)
{
    database_->StoreConnection(conection);
}

void StorageControllerImpl::RequestConnections(std::vector<common::ConnectionInfo>& connections)
{
    connections = database_->RequestConnections();
}

void StorageControllerImpl::RemoveConnection(const common::ConnectionInfo & conection)
{
    database_->RemoveConnection(conection);
}


void StorageControllerImpl::StoreMetrics(const common::MonitoringData& data)
{
    std::vector<common::MonitoringData> metrics = {data};
    if(sizeCheck())
    {
        database_->Rotate(static_cast<uint32_t>(1));
    }
    database_->StoreMetrics(metrics);
}

void StorageControllerImpl::StoreMetrics(const std::vector<common::MonitoringData>& data)
{
    if(sizeCheck())
    {
        database_->Rotate(static_cast<uint32_t>(data.size()));
    }
    database_->StoreMetrics(data);

}

void StorageControllerImpl::LoadMetrics(std::vector<common::MonitoringData>& data)
{
    data = database_->LoadMetrics();
}

void StorageControllerImpl::RequestMetrics(std::vector<common::MonitoringData>& data)
{
    data = database_->GetMetrics();
}

bool StorageControllerImpl::sizeCheck()
{
    auto options = database_->LoadMonitoringOptions();
    auto size = database_->GetDatabaseSize();
    return size <= options.MaxStorageSize_;
}

}