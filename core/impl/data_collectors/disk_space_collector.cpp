/// \file disk_space_collector.cpp
/// \brief реализация сборщика данных о свободном месте на жёстком диске

#include "disk_space_collector.h"

#include <boost/algorithm/string/join.hpp>

namespace core
{

DiskSpaceCollector::DiskSpaceCollector(std::shared_ptr<deviceController::DataReceiver> data,
    std::shared_ptr<common::metricOptions::MetricSettings> diskOptions)
    : data_{data}
    , diskOptions_{diskOptions}
{

}

DiskSpaceCollector::~DiskSpaceCollector()
{
}

common::collectingMetrics::MetricIds DiskSpaceCollector::GetMetricName()
{
    return common::collectingMetrics::FreeDiskSpace;
}

std::string DiskSpaceCollector::GetData(deviceState::paramStates& systemState)
{
    std::shared_ptr<std::vector<std::string>> sizes = {};
    try
    {
        sizes = data_->GetDriveSpace();
    }
    catch(std::exception)
    {
        systemState = deviceState::ErrorWhileCollecting;
        return "";
    }

    std::string stringData = boost::algorithm::join(*sizes, ",");

    if(check(sizes))
    {
        systemState = deviceState::Ok;
    }
    else
    {
        systemState = deviceState::NotNormal;
    }
    return stringData;
}

bool DiskSpaceCollector::check(std::shared_ptr<std::vector<std::string>> data)
{
   for (auto discSize:*data)
   {
       auto spacePlace = discSize.find(" ");
       if(spacePlace == -1)
       {
           return false;
       }
       auto sizeString = discSize.substr(spacePlace+1);
       auto DigitSize = std::stoi(sizeString);

       auto DiscName = discSize.substr(0,spacePlace-1);

       for(auto option:(*diskOptions_).freeSpace)
       {
           if(option.DiscName == DiscName)
           {
               if(DigitSize < option.MinimalFreeSpace)
               {
                    return false;
               }
               else
               {
                   break;
               }
           }
       }
   }
   return true;
}

}