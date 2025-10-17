/* formatkit C++ stable 1 */
#include "formatkit.h"
#include <iostream>
#include <unordered_map>

/* Foregrounds colors */
static std::unordered_map<std::wstring, std::wstring> fgColors = {
    {L"black", L"30"},{L"red", L"31"},{L"green", L"32"},{L"yellow", L"33"},
    {L"blue", L"34"},{L"magenta", L"35"},{L"cyan", L"36"},{L"white", L"37"},
    {L"gray", L"90"},{L"bright_red", L"91"},{L"bright_green", L"92"},
    {L"bright_yellow", L"93"},{L"bright_blue", L"94"},{L"bright_magenta", L"95"},
    {L"bright_cyan", L"96"},{L"bright_white", L"97"}
};

/* Background colors */
static std::unordered_map<std::wstring, std::wstring> bgColors = {
    {L"black", L"40"},{L"red", L"41"},{L"green", L"42"},{L"yellow", L"43"},
    {L"blue", L"44"},{L"magenta", L"45"},{L"cyan", L"46"},{L"white", L"47"},
    {L"gray", L"100"},{L"bright_red", L"101"},{L"bright_green", L"102"},
    {L"bright_yellow", L"103"},{L"bright_blue", L"104"},{L"bright_magenta", L"105"},
    {L"bright_cyan", L"106"},{L"bright_white", L"107"}
};

/* Formatting Options */
static std::unordered_map<std::wstring, std::wstring> formats = {
    {L"reset", L"0"},{L"bold", L"1"},{L"dim", L"2"},{L"italic", L"3"},
    {L"underline", L"4"},{L"blink", L"5"},{L"invert", L"7"},{L"strikethrough", L"9"}
};

/* Universal Print Function */
void print(const std::wstring& text,
    const std::wstring& fgColor,
    const std::wstring& format,
    const std::wstring& bgColor)
{
    std::wstring fg = fgColors.count(fgColor) ? fgColors[fgColor] : L"";
    std::wstring bg = bgColors.count(bgColor) ? bgColors[bgColor] : L"";
    std::wstring fmt = formats.count(format) ? formats[format] : L"";

    std::wstring code = L"\033[";

    bool first = true;
    if (!fmt.empty()) { code += fmt; first = false; }
    if (!fg.empty()) { code += (first ? L"" : L";") + fg; first = false; }
    if (!bg.empty()) { code += (first ? L"" : L";") + bg; }
    code += L"m";

    std::wcout << L"\033[0m" << code << text << L"\033[0m";
}
