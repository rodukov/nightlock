#pragma once
#include "Entry.h"
#include <string>
#include <vector>

// Represents a group (folder) of password entries
struct Group {
    std::wstring groupName; // foldername
    std::vector<Entry> entries; // linked entries
    std::vector<Group> subGroups; // subfolders (underfolder directories)
    std::wstring decoration; // group customization (optional)
};