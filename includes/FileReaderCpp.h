#ifndef FILEREADERCPP_H
#define FILEREADERCPP_H

#include <fstream>
#include <optional>
#include "IFileReader.h"

class FileReaderCpp : public IFileReader
{
    private:
        std::ifstream ifs;
        bool fileExists();
    public:
        FileReaderCpp(char* filePath);
        ~FileReaderCpp();
        std::optional<std::string> readLine();
};

#endif // FILEREADERCPP_H
