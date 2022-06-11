/// \file options_io.cpp
/// \brief реализация чтения записи и генерации настроек

#include "options_io.h"
#include "options_constants.h"

#pragma warning( disable : 4996 )
#   include "rapidjson/document.h"
#pragma warning(default: 4996 )

#include <fstream>
#include <stdexcept>

using namespace rapidjson;

namespace internalStorage
{
OptionsIo::OptionsIo(std::shared_ptr<DatabaseController> storage)
    : storage_{storage}
{

}

void OptionsIo::ReadOptions(const std::string& path)
{
    /// быстрое чтение из файла
    std::ifstream f(path);
    if(!f.is_open())
    {
        throw std::runtime_error(u8"file not opened");
    }
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string options(size, ' ');
    f.seekg(0);
    f.read(&options[0], size);

    Document document;
    document.Parse(options.c_str());

    auto monitoringOptionsObj = document[constants::MonitoringOptions].GetObject();

}

}