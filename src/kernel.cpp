#include "formatkit.h"
#include "Manager.h"
#include "livecmd.h"
#include "init.h"

#include "json.hpp"
#include <openssl/evp.h>

#include <iostream>
using json = nlohmann::json;

int main() {

    init();

    print(L"[   OK   ]", L"yellow", L"bold");
    std::wcout << L" -> Included ";
    std::wcout << OpenSSL_version(OPENSSL_VERSION) << std::endl;
    Manager manager;
    manager.init();
    livecmd shell(&manager); // manager address
    shell.run();

    return 0;
}
