/// \file encoding_helper.cpp
/// \brief реализация функций, переводящих кодировки юникода

#include "encoding_helper.h"

#include <Poco/UnicodeConverter.h>

namespace common
{
namespace encoding_helper
{

std::string ws2s(std::wstring &ws)
{
    std::string temp = {};
    Poco::UnicodeConverter::toUTF8(ws, temp);
    return temp;
}

std::wstring s2ws(std::string &s)
{
    std::wstring temp = {};
    Poco::UnicodeConverter::toUTF16(s, temp);
    return temp;
}

}
}
