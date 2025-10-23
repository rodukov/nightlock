#include <init.h>

#include <iostream>
#include <windows.h>
#include <locale>

void init() {
    try { std::locale::global(std::locale("en_US.utf8")); }
    catch (...) { std::wcerr << L"Не удалось установить локаль UTF-8\n"; }
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());

    /* Windows UTF-8 + ANSI */
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    #endif
}