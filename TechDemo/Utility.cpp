#include "Utility.h"
#include <fstream>

void ThrowIfNotOk(HRESULT result, const std::string& message)
{
	if (result != S_OK)
	{
		throw std::runtime_error(message);
	}
}

std::vector<char> ReadByteArray(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open " + filename);
	}
	size_t pos = file.tellg();

	std::vector<char> result(pos);

	file.seekg(0, std::ios::beg);
	file.read(&result[0], pos);

	return result;
}