#ifndef FILEREADERC_HPP
#define FILEREADERC_HPP

#include <optional>
#include <string>
#include "Common.hpp"
#include "IFileReader.hpp"

class FileReaderC : public IFileReader
{
    private:
        int currPos = 0;
        void* strBuf;
        int strBufSize = 0;
        FILE *pF;
        bool isEof = false;
        ErrorCode getNextEol(int * nextEolPos, bool * isCrPresent);
        ErrorCode setBuffer();
    public:
        FileReaderC(char* filePath);
        ~FileReaderC();
        std::optional<std::string> readLine();
};

#endif // FILEREADERC_HPP
