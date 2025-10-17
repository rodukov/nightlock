#pragma once
#include "Manager.h"

#include <string>
#include <map>
#include <functional>
#include <unordered_map>

class livecmd {
public:
    livecmd(Manager *manager);
    void run();
private:
    Manager* manager;
    std::map<std::wstring, std::function<void()>> commands;

    /* livecmd shellmethods */
    void help();
    void logout();
    void clc();
    void version();

    /* livecmd shellmanager methods */
    void newpass();
    void showtree();
    void deletepass();
    void newgroup();
    void directpass();
    void lsroot();
    void lsdirect();
    void deletedirect();
    void deletegroup();
    void viewpass();
    void directview();
    void savedb();
};
