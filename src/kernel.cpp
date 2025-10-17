#include "formatkit.h"
#include "Manager.h"
#include "livecmd.h"

#include "json.hpp"

#include <iostream>
#include <windows.h>
#include <locale>

using json = nlohmann::json;

int main() {

    try { std::locale::global(std::locale("en_US.utf8")); }
    catch(...) { std::wcerr << L"[⚠️] Не удалось установить локаль UTF-8\n"; }
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());

    // Консоль Windows UTF-8 + ANSI
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

    print(L"Менеджер паролей alpha-0.1\n", L"white", L"bold", L"blue");

    Manager manager;
    manager.init();
    livecmd shell(&manager); // manager address
    shell.run();

    return 0;
}
