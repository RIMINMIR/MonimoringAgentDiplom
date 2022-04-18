/// \file encoding_helper.h
/// \brief определение функций, переводящих кодировки юникода

#pragma once
#ifndef COMMON_ENCODING_HELPER_H
#define COMMON_ENCODING_HELPER_H

#include "string"

namespace common
{
namespace encoding_helper
{

/// \brief функция перевода из wstring в string
/// \param ws строка  в формате wstring
std::string ws2s(const std::wstring &ws);

/// \brief функция перевода из string в wstring
/// \param ws строка  в формате string
std::wstring s2ws(const std::string &s);

}
}
#endif