#include <iostream>
#include <fstream>
#include "FileReaderCpp.h"

FileReaderCpp::FileReaderCpp(char* filePath)
{
    ifs.open(filePath, std::ifstream::in);
    
    if(ifs.bad() || !ifs.is_open())
    {
        throw FILE_ACCESS_ERROR;
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
    return "ToDO";
}