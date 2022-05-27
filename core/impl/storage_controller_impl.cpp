/// \file storage_controller_impl.cpp
/// \brief  реализация контроллера внутреннего хранилища

#include "storage_controller_impl.h"

namespace core
{

StorageControllerImpl::StorageControllerImpl()
{

}

StorageControllerImpl::~StorageControllerImpl()
{

}

void StorageControllerImpl::StoreOptions(const common::MonitoringOptions& options)
{

}

void StorageControllerImpl::RequestOptions(common::MonitoringOptions& options)
{

}

void StorageControllerImpl::StoreConnection(const common::ConnectionInfo & conection)
{

}

void StorageControllerImpl::RequestConnections(std::vector<common::ConnectionInfo>& connections)
{

}

void StorageControllerImpl::RemoveConnection(const common::ConnectionInfo & conection)
{

}


void StorageControllerImpl::StoreMetrics(const common::MonitoringData& data)
{

}

void StorageControllerImpl::StoreMetrics(const std::vector<common::MonitoringData>& data)
{

}

void StorageControllerImpl::LoadMetrics(std::vector<common::MonitoringData>& data)
{

}

void StorageControllerImpl::RequestMetrics(std::vector<common::MonitoringData>& data)
{

}

}