#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::wstring> split(
    const std::wstring& path,
    wchar_t delimiter)
{
    std::vector<std::wstring> parts;
    std::wstringstream ss(path);
    std::wstring item;

    while (std::getline(ss, item, delimiter)) {
        if (!item.empty())
            parts.push_back(item);
    }

    return parts;
}