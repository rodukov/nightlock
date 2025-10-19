#include "Manager.h"

#include <sys/stat.h>  // для mkdir (создание папки)
#include <direct.h>    // для _mkdir на Windows
#include <fstream>
#include <filesystem>
#include <functional>
#include <codecvt>
#include "json.hpp"
#include "formatkit.h"

using json = nlohmann::json;

void Manager::init() {
    std::ifstream file("db/main.json");

    if (!file.good()) {
        print(L"[?] main.json not found", L"white", L"bold", L"red");
        std::wcout << std::endl;
        save();
    }
    else {
        print(L"[+] loading main.json", L"white", L"bold", L"blue");
        std::wcout << std::endl;
        load();
    }
}
// ---------- утилиты конверсии ----------
static inline std::string wstring_to_utf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

static inline std::wstring utf8_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(str);
}

// ---------- сохранение ----------
void Manager::save() {
    json j;
    j["rootEntries"] = json::array();
    j["rootGroups"] = json::array();

    // rootEntries
    for (const auto& e : rootEntries) {
        json entry;
        entry["NAME"] = wstring_to_utf8(e.NAME);
        entry["LOGIN"] = wstring_to_utf8(e.LOGIN);
        entry["PASSWD"] = wstring_to_utf8(e.PASSWD);
        entry["URL"] = wstring_to_utf8(e.URL);
        entry["NOTE"] = wstring_to_utf8(e.NOTE);

        entry["DECORATION"] = {
            {"FOREGROUD", wstring_to_utf8(e.DECORATION.FOREGROUD)},
            {"BACKGROUND", wstring_to_utf8(e.DECORATION.BACKGROUND)},
            {"FORMAT", wstring_to_utf8(e.DECORATION.FORMAT)},
            {"ICON", wstring_to_utf8(e.DECORATION.ICON)}
        };

        j["rootEntries"].push_back(entry);
    }

    // рекурсивная лямбда для групп
    std::function<json(const Group&)> group_to_json;
    group_to_json = [&](const Group& g) -> json {
        json gj;
        gj["groupName"] = wstring_to_utf8(g.groupName);
        gj["decoration"] = wstring_to_utf8(g.decoration);
        gj["entries"] = json::array();
        gj["subGroups"] = json::array();

        for (const auto& e : g.entries) {
            json entry;
            entry["NAME"] = wstring_to_utf8(e.NAME);
            entry["LOGIN"] = wstring_to_utf8(e.LOGIN);
            entry["PASSWD"] = wstring_to_utf8(e.PASSWD);
            entry["URL"] = wstring_to_utf8(e.URL);
            entry["NOTE"] = wstring_to_utf8(e.NOTE);
            entry["DECORATION"] = {
                {"FOREGROUD", wstring_to_utf8(e.DECORATION.FOREGROUD)},
                {"BACKGROUND", wstring_to_utf8(e.DECORATION.BACKGROUND)},
                {"FORMAT", wstring_to_utf8(e.DECORATION.FORMAT)},
                {"ICON", wstring_to_utf8(e.DECORATION.ICON)}
            };
            gj["entries"].push_back(entry);
        }

        for (const auto& sg : g.subGroups) {
            gj["subGroups"].push_back(group_to_json(sg));
        }

        return gj;
        };

    for (const auto& g : rootGroups) {
        j["rootGroups"].push_back(group_to_json(g));
    }

    // создаём папку db вручную
#ifdef _WIN32
    _mkdir("db");
#else
    mkdir("db", 0777);
#endif

    std::ofstream file("db/main.json", std::ios::binary);
    if (!file.is_open()) {
        print(L"[ ERROR ] cannot open db/main.json", L"white", L"bold", L"red");
        std::wcout << std::endl;
        return;
    }

    file << j.dump(4);
    file.close();

    print(L"[ KERNEL ] dumped", L"white", L"bold", L"blue");
    std::wcout << std::endl;
}

// ---------- загрузка ----------
void Manager::load() {
    std::ifstream file("db/main.json", std::ios::binary);
    if (!file.good()) {
        print(L"[ KERNEL ] main.json not found", L"white", L"bold", L"red");
        std::wcout << std::endl;
        return;
    }

    json j;
    try {
        file >> j;
    }
    catch (...) {
        print(L"[ ERROR ] failed to parse db/main.json", L"white", L"bold", L"red");
        std::wcout << std::endl;
        return;
    }
    file.close();

    rootEntries.clear();
    rootGroups.clear();

    // rootEntries
    if (j.contains("rootEntries")) {
        for (const auto& ej : j["rootEntries"]) {
            Entry e;
            e.NAME = utf8_to_wstring(ej.value("NAME", ""));
            e.LOGIN = utf8_to_wstring(ej.value("LOGIN", ""));
            e.PASSWD = utf8_to_wstring(ej.value("PASSWD", ""));
            e.URL = utf8_to_wstring(ej.value("URL", ""));
            e.NOTE = utf8_to_wstring(ej.value("NOTE", ""));
            if (ej.contains("DECORATION")) {
                auto d = ej["DECORATION"];
                e.DECORATION.FOREGROUD = utf8_to_wstring(d.value("FOREGROUD", ""));
                e.DECORATION.BACKGROUND = utf8_to_wstring(d.value("BACKGROUND", ""));
                e.DECORATION.FORMAT = utf8_to_wstring(d.value("FORMAT", ""));
                e.DECORATION.ICON = utf8_to_wstring(d.value("ICON", ""));
            }
            rootEntries.push_back(e);
        }
    }

    // рекурсивная загрузка групп
    std::function<Group(const json&)> json_to_group;
    json_to_group = [&](const json& gj) -> Group {
        Group g;
        g.groupName = utf8_to_wstring(gj.value("groupName", ""));
        g.decoration = utf8_to_wstring(gj.value("decoration", ""));
        if (gj.contains("entries")) {
            for (const auto& ej : gj["entries"]) {
                Entry e;
                e.NAME = utf8_to_wstring(ej.value("NAME", ""));
                e.LOGIN = utf8_to_wstring(ej.value("LOGIN", ""));
                e.PASSWD = utf8_to_wstring(ej.value("PASSWD", ""));
                e.URL = utf8_to_wstring(ej.value("URL", ""));
                e.NOTE = utf8_to_wstring(ej.value("NOTE", ""));
                if (ej.contains("DECORATION")) {
                    auto d = ej["DECORATION"];
                    e.DECORATION.FOREGROUD = utf8_to_wstring(d.value("FOREGROUD", ""));
                    e.DECORATION.BACKGROUND = utf8_to_wstring(d.value("BACKGROUND", ""));
                    e.DECORATION.FORMAT = utf8_to_wstring(d.value("FORMAT", ""));
                    e.DECORATION.ICON = utf8_to_wstring(d.value("ICON", ""));
                }
                g.entries.push_back(e);
            }
        }
        if (gj.contains("subGroups")) {
            for (const auto& sj : gj["subGroups"]) {
                g.subGroups.push_back(json_to_group(sj));
            }
        }
        return g;
        };

    if (j.contains("rootGroups")) {
        for (const auto& gj : j["rootGroups"]) {
            rootGroups.push_back(json_to_group(gj));
        }
    }

    print(L"[ KERNEL ] main.json loaded", L"white", L"bold", L"blue");
    std::wcout << std::endl;
}