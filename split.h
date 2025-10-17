#pragma once

#include <vector>
#include <string>
#include <iostream>

/*
The splitPath function takes a path string and splits it
into parts using a separator (default '/')
Returns a vector of wstrings,
each of which is one path segment.
*/
std::vector<std::wstring> split(
	const std::wstring& path,
	wchar_t delimiter = L'/');