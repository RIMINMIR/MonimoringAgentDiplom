/// \file dir_helper.cpp
/// \brief функция для смены рабочей директории

#include "dir_helper.h"
#include <string>
#include "Windows.h"

namespace win_service
{

void ChangeWorkingDirectory()
{
    std::string fileDir = CMAKE_BINPATH;
    fileDir += u8"/windows_service/bin/";
    LPCSTR point = fileDir.c_str();
    SetCurrentDirectory(point);
}
}