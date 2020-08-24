#include "Util.h"

#include <fstream>
#include <iostream>

std::vector<char> readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to load file: " << filename << std::endl;
        exit(0);
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.clear();
    
    return buffer;
}
