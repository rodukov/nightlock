#include "Manager.h"
#include "split.h"
#include "formatkit.h"

#include <vector>
#include <string>
#include <iostream>
#include <locale>

/*
Root Directory Methods Implementation
*/
void Manager::addRootEntry(
	const std::wstring& NAME,
	const std::wstring& LOGIN,
	const std::wstring& PASSWD,
	const std::wstring& URL,
	const std::wstring& NOTE,
	const DECORATION DECORATION)
{
	rootEntries.push_back({ NAME, LOGIN, PASSWD, URL, NOTE, DECORATION });
}

void Manager::removeRootEntry(
	const std::wstring& NAME
) {
	for (auto object = rootEntries.begin(); object != rootEntries.end(); ++object)
	if (object->NAME == NAME) { rootEntries.erase(object); return; }
	
}

void Manager::printRootNames() {
	for (auto& object : rootEntries) std::wcout << object.NAME << std::endl;
}

Entry* Manager::getRootEntry(const std::wstring& NAME) {
	for (auto& object : rootEntries) if (object.NAME == NAME) return &object;
	return nullptr;
}
/*
Group Methods Implementation
*/

// complex
Group* Manager::getGroup(const std::wstring& path) {
    auto parts = split(path);
    std::vector<Group>* level = &rootGroups;

    for (auto& part : parts) {
        bool found = false;
        for (auto& group : *level) {
            if (group.groupName == part) {
                found = true;
                if (part == parts.back()) return &group;
                level = &group.subGroups;
                break;
            }
        }
        if (!found) return nullptr;
    }

    return nullptr;
}

Entry* Manager::getGroupEntry(
    const std::wstring& path,
    const std::wstring& NAME)
{
    Group* grp = getGroup(path);
    for (auto& object : grp->entries) {
        if (object.NAME == NAME) return &object;
    }
}

// complex
Group* Manager::createGroup(const std::wstring& path) {
    auto parts = split(path);
    std::vector<Group>* currentLevel = &rootGroups;
    Group* lastGroup = nullptr;

    for (auto& part : parts) {
        bool found = false;

        // Switches to downlevel(exists)
        for (auto& group : *currentLevel) {
            if (group.groupName == part) {
                lastGroup = &group;
                currentLevel = &group.subGroups;
                found = true;
                break;
            }
        }
        // Creates new directory(not exists)
        if (!found) {
            Group newGroup;
            newGroup.groupName = part;
            currentLevel->push_back(newGroup);

            lastGroup = &currentLevel->back();
            currentLevel = &lastGroup->subGroups;
        }
    }

    return lastGroup;
}

void Manager::addGroupEntry(
    const std::wstring& path,
    const std::wstring& NAME,
    const std::wstring& LOGIN,
    const std::wstring& PASSWD,
    const std::wstring& URL,
    const std::wstring& NOTE,
    DECORATION DECORATION)
{
    Group* X = getGroup(path);
    X->entries.push_back({ NAME, LOGIN, PASSWD, URL, NOTE, DECORATION });
}

void Manager::removeGroupEntry(const std::wstring& path, const std::wstring& NAME) {
    // Получаем указатель на группу
    Group* grp = getGroup(path);
    if (!grp) return; // защита от nullptr

    // Удаляем все Entry с нужным NAME
    grp->entries.erase(
        std::remove_if(
            grp->entries.begin(),
            grp->entries.end(),
            [&](const Entry& e) { return e.NAME == NAME; }
        ),
        grp->entries.end()
    );
}
void Manager::removeGroup(const std::wstring& path) {
    // Разбиваем путь на части
    std::vector<std::wstring> parts;
    std::wstring temp;
    for (wchar_t ch : path) {
        if (ch == L'/') {
            if (!temp.empty()) parts.push_back(temp);
            temp.clear();
        }
        else {
            temp.push_back(ch);
        }
    }
    if (!temp.empty()) parts.push_back(temp);

    // Если путь пустой, ничего не делаем
    if (parts.empty()) return;

    // Начинаем с корня
    std::vector<Group>* currentGroups = &rootGroups; // предположим, что Manager хранит vector<Group> rootGroups

    for (size_t i = 0; i < parts.size(); ++i) {
        bool found = false;
        for (auto it = currentGroups->begin(); it != currentGroups->end(); ++it) {
            if (it->groupName == parts[i]) {
                if (i == parts.size() - 1) {
                    // Это последняя группа в пути — удаляем её полностью
                    currentGroups->erase(it);
                    return;
                }
                else {
                    // Переходим в подгруппы
                    currentGroups = &it->subGroups;
                    found = true;
                    break;
                }
            }
        }
        if (!found) return; // Группа не найдена — выходим
    }
}


void Manager::printGroupEntriesNames(const std::wstring& path) {
    Group* X = getGroup(path);
    for (auto& Y : X->entries) {
        std::wcout << Y.NAME << std::endl;
    }
}

/* complex tree */
void printTree(const std::vector<Group>& groups, const std::wstring& prefix = L"") {
    for (size_t i = 0; i < groups.size(); ++i) {
        const auto& group = groups[i];
        bool isLastGroup = (i == groups.size() - 1);

        std::wcout << prefix;
        std::wcout << (isLastGroup ? L"└───" : L"├───") << group.groupName << L"/" << std::endl;

        // Печатаем все записи внутри группы
        for (size_t j = 0; j < group.entries.size(); ++j) {
            bool isLastEntry = (j == group.entries.size() - 1) && group.subGroups.empty();
            std::wcout << prefix;
            std::wcout << (isLastGroup ? L"    " : L"│   ");
            std::wcout << (isLastEntry ? L"└───" : L"├───") << group.entries[j].NAME << std::endl;
        }

        // Рекурсивно печатаем подгруппы
        std::wstring newPrefix = prefix + (isLastGroup ? L"    " : L"│   ");
        printTree(group.subGroups, newPrefix);
    }
}

void Manager::tree() {

    print(L"Root/", L"white", L"bold", L"red");
    std::wcout << std::endl;
    // Печатаем корневые записи
    for (size_t i = 0; i < rootEntries.size(); ++i) {
        std::wcout << L"├───" << rootEntries[i].NAME << std::endl;
    }

    // Печатаем все группы рекурсивно
    printTree(rootGroups);
}