#ifndef FILEREADERAPP_HPP
#define FILEREADERAPP_HPP

#include <iostream>
#include <string>
#include "Common.hpp"
#include "IFileReader.hpp"
#include "FileReaderC.hpp"
#include "FileReaderCpp.hpp"

class FileReaderApp
{
private:
    const int req_arg_num = 4;
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

public:
    static FileReaderApp* ms_instance;
    static FileReaderApp* Instance(int argc, char** argv);
    static void Release();
    ErrorCode process();


};

#endif // FILEREADERAPP_HPP
