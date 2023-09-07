#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "FileReaderCpp.hpp"

FileReaderCpp::FileReaderCpp(char* filePath)
{
    ifs.open(filePath, std::ifstream::in);

    if(ifs.bad() || !ifs.is_open())
    {
        throw FileReaderException::FILE_ACCESS_ERROR;
    }
}

FileReaderCpp::~FileReaderCpp()
{
    if(ifs.is_open())
    {
        ifs.close();
    }
}

std::optional<std::string> FileReaderCpp::readLine()
{
    std::string result;

    if (ifs.bad() || ifs.eof())
    {
        return std::nullopt;
    }
    std::getline(ifs, result);

    return result;
}