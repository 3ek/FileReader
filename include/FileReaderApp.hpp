#ifndef FILEREADERAPP_HPP
#define FILEREADERAPP_HPP

#include <iostream>
#include <string>
#include "Common.hpp"
#include "IFileReader.hpp"
#include "FileReaderC.hpp"
#include "FileReaderCpp.hpp"

enum class FileReaderArgumentException
{
    ARG_INVALID_NUM = 0xBABA
};

class FileReaderApp
{
private:
    char* filePath;
    int codeMethod;
    int numOfLines;
    ErrorCode status;
    IFileReader *fileReader {nullptr};
    std::string helpStr {"--help"};
    FileReaderApp(const FileReaderApp&) = delete;
    FileReaderApp& operator=(const FileReaderApp&) = delete;
    FileReaderApp(FileReaderApp&&) = delete;
    FileReaderApp& operator=(FileReaderApp&&) = delete;
    FileReaderApp(int argc, char** argv);
    ~FileReaderApp();
    ErrorCode checkArgs(int argc, char** argv);
    ErrorCode prepare();
    void helpDisplay();
    int argToInt(char* charString);
    bool isNumber(std::string checkStr);

public:
    static FileReaderApp* ms_instance;
    static FileReaderApp* instance(int argc, char** argv);
    static void release();
    ErrorCode process();


};

#endif // FILEREADERAPP_HPP
