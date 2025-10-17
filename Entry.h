#pragma once
#include <iostream>

struct DECORATION {
	std::wstring FOREGROUD;
	std::wstring BACKGROUND;
	std::wstring FORMAT;
	std::wstring ICON;
};

struct Entry {
	std::wstring NAME; // entryname(uid)
	std::wstring LOGIN; // login(username)
	std::wstring PASSWD; // password
	std::wstring URL; // servicelink (optional)
	std::wstring NOTE; // entrycomment (optional)
	DECORATION DECORATION; // entry customization (optional)
};