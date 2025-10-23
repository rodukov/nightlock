#include "Manager.h"
#include "readsecret.h"
#include "formatkit.h"
#include "Crypt.h"
#include "livecmd/alert.h"
#include "utils.h"
#include "json.hpp"

#include <sys/stat.h>  // для mkdir (создание папки)
#include <direct.h>    // для _mkdir на Windows
#include <fstream>
#include <filesystem>
#include <functional>

using json = nlohmann::json;

void Manager::init() {
    std::ifstream file("db/primary.nightlock");

    if (!file.good()) {
        alert::db::notfound();
        save();
    }
    else {
        alert::db::found();
        load();
    }
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

    std::ofstream file("db/primary.nightlock1", std::ios::binary);
    if (!file.is_open()) {
        alert::db::not_open();
        return;
    }

    file << j.dump(4);
    file.close();

    alert::db::createmaster();
    encrypt_file("db/primary.nightlock1", "db/primary.nightlock", wstring_to_string(readsecret()));

    alert::db::save();
}

// ---------- загрузка ----------
void Manager::load() {

    alert::db::readmaster();
    decrypt_file("db/primary.nightlock", "db/primary.nightlock1", wstring_to_string(readsecret()));

    std::ifstream file("db/primary.nightlock1", std::ios::binary);
    if (!file.good()) {
        alert::db::incorrectmaster();
        exit(0);
        return;
    }

    json j;
    try {
        file >> j;
    }
    catch (...) {
        alert::db::incorrectmaster();
        alert::db::incorrectmaster();
        exit(0);
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

    alert::db::load();
}

void Manager::close() {
    if (std::remove("db/primary.nightlock1") == 0) {
        alert::db::close();
    }
}