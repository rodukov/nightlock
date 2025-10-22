#pragma once
#include <openssl/evp.h>
#include <openssl/err.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool encrypt_file(const std::string& inputFile, const std::string& outputFile, const std::string& password);
bool decrypt_file(const std::string& inputFile, const std::string& outputFile, const std::string& password);