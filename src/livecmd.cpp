#include "livecmd.h"
#include "formatkit.h"
#include "Manager.h"
#include "readsecret.h"

#include <iostream>
#include <algorithm>
#include <locale>
#include <conio.h>
#include <string>
#include <windows.h>

static std::unordered_map<std::wstring, std::wstring> helplist = {
    {L"help", L"показывает данное сообщение"},
    {L"version", L"показыает версию программного обеспечения"},
    {L"logout", L"выход из программного обеспечения"},
    {L"clc", L"очистка экрана"},
    {L"tree", L"выводит общее дерево"},
    {L"newpass", L"создает новый пароль в Root/ директории"},
    {L"deletepass", L"удаляет пароль в Root/ директории"},
    {L"newgroup", L"создает новую директорию"},
    {L"directpass", L"создает новый пароль по необходимому пути"},
    {L"lsroot", L"список паролей (для директории Root/)"},
    {L"lsdirect", L"список паролей (для других директорий)"},
    {L"deletedirect", L"удаляет пароль (для других директорий)"},
    {L"deletegroup", L"удаляет директорию"},
    {L"viewpass", L"просмотр значения пароля (для директории Root/)"},
    {L"directview", L"просмотр значения пароля (для других директорий)"},
    {L"savedb", L"сохранить в базу данных"},
};

livecmd::livecmd(Manager* manager) : manager(manager)
{
    commands = {
        {L"help",   [this]() { help(); }},
        {L"version",   [this]() { version(); }},
        {L"logout", [this]() { logout(); }},
        {L"clc",    [this]() { clc(); }},
        {L"tree",    [this]() { showtree(); }},
        {L"newpass",    [this]() { newpass(); }},
        {L"deletepass",    [this]() { deletepass(); }},
        {L"newgroup",    [this]() { newgroup(); }},
        {L"directpass",    [this]() { directpass(); }},
        {L"lsroot",    [this]() { lsroot(); }},
        {L"lsdirect",    [this]() { lsdirect(); }},
        {L"deletedirect",    [this]() { deletedirect(); }},
        {L"deletegroup",    [this]() { deletegroup(); }},
        {L"viewpass",    [this]() { viewpass(); }},
        {L"directview",    [this]() { directview(); }},
        {L"savedb",    [this]() { savedb(); }},
    };
}

void livecmd::run() {
    std::wstring input;
    print(L"Менеджер паролей alpha-0.1\n", L"white", L"bold", L"blue");
    print(L"Выполнен вход в livecmd. Введите help для списка команд.\n\n", L"white");
    SetConsoleTitleW(L"nightlock livecmd");
    while (true) {
        std::wcout << L"root/ > ";
        if (!std::getline(std::wcin, input)) break; /* EOF check */
        std::transform(input.begin(), input.end(), input.begin(), ::towlower); /* lowercase transform */

        auto it = commands.find(input);
        if (it != commands.end()) it->second();
        else std::wcout << L"Неизвестная команда: " << input << L". Введите 'help'.\n";

        std::wcout << std::endl;

    }
}

void livecmd::help() {
    print(L"Nightlock список команд", L"white", L"bold", L"blue");
    std::wcout << std::endl;
    for (const auto& c : commands) {
        int counter = 15;
        auto it = helplist.find(c.first);
        if (it != helplist.end()) {
            counter = counter - c.first.size();
            std::wcout << c.first;
            for (int i = 0; i < counter; i++) {
                std::wcout << L" ";
            }
            std::wcout << it->second << L"\n";
        }
        
    }
}

void livecmd::logout() {
    manager->close();
    exit(0);
}

void livecmd::clc() {
    std::wcout << L"\033[2J\033[H";
}

void livecmd::version() {
    print(L"Менеджер паролей nightlock alpha-0.1\n", L"white", L"bold", L"blue");
}


/* livecmd shellmanager */
void livecmd::newpass() {

    print(L"[+] Создание пароля в Root/", L"white", L"blink", L"blue");
    std::wcout << std::endl;
    std::wcout << std::endl;
    print(L"Введите название пароля > ", L"white", L"italic");
    std::wstring name; std::getline(std::wcin, name);

    print(L"Введите имя пользоватя > ", L"white", L"italic");
    std::wstring login; std::getline(std::wcin, login);

    print(L"Введите пароль > ", L"white", L"italic");
    std::wstring passwd = readsecret();

    print(L"Повторите введённый пароль > ", L"white", L"italic");
    std::wstring rpasswd = readsecret();

    print(L"Добавьте адрес пароля (необяз.) > ", L"white", L"italic");
    std::wstring url; std::getline(std::wcin, url);

    print(L"Добавьте заметку (необяз.) > ", L"white", L"italic");
    std::wstring note; std::getline(std::wcin, note);

    if (passwd != rpasswd) {
        print(L"Введённые пароли не совпадают!/", L"white", L"blink", L"red");
        return;
    }

    manager->addRootEntry(name, login, passwd, url, note, { L"", L"", L"", L"" });
    print(L"Добавлено.", L"white", L"bold", L"green");
}
void livecmd::showtree() {
    manager->tree();
}

void livecmd::deletepass() {

    print(L"[-] Удаление пароля в Root/", L"white", L"blink", L"blue");
    std::wcout << std::endl;
    std::wcout << std::endl;
    print(L"Введите название пароля > ", L"white", L"italic");
    std::wstring name; std::getline(std::wcin, name);

    print(L"[?] Вы действительно хотите удалить пароль? [Да/нет] >", L"red", L"underline");
    std::wstring ans; std::getline(std::wcin, ans);
    if (ans == L"Да") {
        manager->removeRootEntry(name);
        print(L"Удалено.", L"white", L"bold", L"red");
    }
    else {
        print(L"Отмена.", L"white", L"bold", L"red");
        return;
    }

}

void livecmd::newgroup() {
    print(L"[+] Создание директории", L"white", L"blink", L"blue");
    std::wcout << std::endl;
    std::wcout << std::endl;
    print(L"Введите путь директорий > ", L"white", L"italic");
    std::wstring path; std::getline(std::wcin, path);
    manager->createGroup(path);

    print(L"Добавлено.", L"white", L"bold", L"green");
}

void livecmd::directpass() {
    print(L"[+] Создание direct-пароля", L"white", L"blink", L"blue");
    std::wcout << std::endl;
    std::wcout << std::endl;
    print(L"Введите путь директорий > ", L"white", L"italic");
    std::wstring path; std::getline(std::wcin, path);

    print(L"Введите название пароля > ", L"white", L"italic");
    std::wstring name; std::getline(std::wcin, name);

    print(L"Введите имя пользоватя > ", L"white", L"italic");
    std::wstring login; std::getline(std::wcin, login);

    print(L"Введите пароль > ", L"white", L"italic");
    std::wstring passwd = readsecret();

    print(L"Повторите введённый пароль > ", L"white", L"italic");
    std::wstring rpasswd = readsecret();

    print(L"Добавьте адрес пароля (необяз.) > ", L"white", L"italic");
    std::wstring url; std::getline(std::wcin, url);

    print(L"Добавьте заметку (необяз.) > ", L"white", L"italic");
    std::wstring note; std::getline(std::wcin, note);

    if (passwd != rpasswd) {
        print(L"Введённые пароли не совпадают!/", L"white", L"blink", L"red");
        return;
    }
    manager->addGroupEntry(path, name, login, passwd, url, note, { L"", L"", L"", L"" });

    print(L"Добавлено.", L"white", L"bold", L"green");

}

void livecmd::lsroot() {
    manager->printRootNames();
}

void livecmd::lsdirect() {
    print(L"Введите путь директорий > ", L"white", L"italic");
    std::wstring path; std::getline(std::wcin, path);

    manager->printGroupEntriesNames(path);
}

void livecmd::deletedirect() {
    print(L"Введите путь директорий > ", L"white", L"italic");
    std::wstring path; std::getline(std::wcin, path);

    print(L"Введите название пароля > ", L"white", L"italic");
    std::wstring name; std::getline(std::wcin, name);

    manager->removeGroupEntry(path, name);
}

void livecmd::deletegroup() {
    print(L"Введите путь директорий > ", L"white", L"italic");
    std::wstring path; std::getline(std::wcin, path);

    manager->removeGroup(path);
}

void livecmd::viewpass() {
    print(L"Введите название пароля > ", L"white", L"italic");
    std::wstring name; std::getline(std::wcin, name);

    Entry* E = manager->getRootEntry(name);
    std::wcout << E->NAME << L"   " << E->LOGIN << L"   " << E->PASSWD << L"   " << E->URL << L"   " << E->NOTE << L"   " << std::endl;
}

void livecmd::directview() {
    print(L"Введите путь директорий > ", L"white", L"italic");
    std::wstring path; std::getline(std::wcin, path);

    print(L"Введите название пароля > ", L"white", L"italic");
    std::wstring name; std::getline(std::wcin, name);

    Entry* E = manager->getGroupEntry(path, name);
    std::wcout << E->NAME << L"   " << E->LOGIN << L"   " << E->PASSWD << L"   " << E->URL << L"   " << E->NOTE << L"   " << std::endl;

}

void livecmd::savedb() {
    manager->save();
}