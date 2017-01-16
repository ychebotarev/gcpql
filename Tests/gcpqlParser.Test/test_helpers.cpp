#include "stdafx.h"
#include "test_helpers.h"

std::wstring test_helpers::StringToWString(const std::string& s)
{
    std::wstring temp(s.length(), L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}
