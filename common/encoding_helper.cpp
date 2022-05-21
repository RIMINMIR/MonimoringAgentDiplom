/// \file encoding_helper.cpp
/// \brief реализация функций, переводящих кодировки юникода

#include "encoding_helper.h"
#include <windows.h>

namespace common
{
namespace encoding_helper
{

std::string ws2s(const std::wstring &ws)
{
     int chars = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);
     std::string s = {};
     s.resize(chars); // или через конструктор wide(wchars_num, 0);
     WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, &s[0], chars, NULL, NULL);
     return s;
}

std::wstring s2ws(const std::string &s)
{
     int wchars_num = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0);
     std::wstring wide = {};
     wide.resize(wchars_num); // или через конструктор wide(wchars_num, 0);
     MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, &wide[0], wchars_num);
     return wide;
}

}
}
