#ifndef FILEREADERCPP_HPP
#define FILEREADERCPP_HPP

#include <fstream>
#include <optional>
#include "IFileReader.hpp"

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

#endif // FILEREADERCPP_HPP
