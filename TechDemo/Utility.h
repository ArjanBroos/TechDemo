#pragma once

#include <Windows.h>
#include <string>
#include <vector>

typedef long HRESULT;

void ThrowIfNotOk(HRESULT result, const std::string& message);
std::vector<char> ReadByteArray(const std::string& filename);