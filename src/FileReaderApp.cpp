#include <iostream>
#include <string>
#include "Common.hpp"
#include "FileReaderApp.hpp"
#include "IFileReader.hpp"
#include "FileReaderC.hpp"
#include "FileReaderCpp.hpp"

FileReaderApp* FileReaderApp::ms_instance{ nullptr };

FileReaderApp::FileReaderApp(int argc, char** argv)
{
    status = ErrorCode::ERROR_SUCCESS;

    if((2 == argc) && (0 == helpStr.compare(argv[1])))
    {
        helpDisplay();
        throw status;
    }

    status = checkArgs(argc, argv);
    if(ErrorCode::ERROR_SUCCESS != status)
    {
        throw status;
    }

    status = prepare();
    if(ErrorCode::ERROR_SUCCESS != status)
    {
        throw status;
    }
}

FileReaderApp::~FileReaderApp()
{
    delete fileReader;
}

FileReaderApp* FileReaderApp::Instance(int argc, char** argv)
{
    if (ms_instance == nullptr) {
        ms_instance = new FileReaderApp{argc, argv};
    }
    return ms_instance;
}

void FileReaderApp::Release()
{
    delete ms_instance;
    ms_instance = nullptr;
}

ErrorCode FileReaderApp::checkArgs(int argc, char** argv)
{
    if(nullptr == argv)
    {
        return ErrorCode::ERROR_INVALID_PTR;
    }

    if(req_arg_num != argc)
    {
        helpDisplay();
        return ErrorCode::ERROR_INVARGS;
    }

    try
    {
        codeMethod = std::stoi(argv[1], nullptr);
    }
    catch (...)
    {
        std::cout << "ERROR: Invalid value in code-method." << std::endl << std::endl;
        helpDisplay();
        return ErrorCode::ERROR_INVARGS;
    }

    if(codeMethod >= METHOD_MAX)
    {
        std::cout << "ERROR: Value out of range in code-method." << std::endl << std::endl;
        helpDisplay();
        return ErrorCode::ERROR_INVARGS;
    }

    try
    {
        numOfLines = std::stoi(argv[3], nullptr);
    }
    catch (...)
    {
        std::cout << "ERROR: Invalid value in number-of-lines." << std::endl << std::endl;
        helpDisplay();
        return ErrorCode::ERROR_INVARGS;
    }

    if(0 > numOfLines)
    {
        std::cout << "ERROR: Value out of range in number-of-lines." << std::endl << std::endl;
        helpDisplay();
        return ErrorCode::ERROR_INVARGS;
    }

    filePath = argv[2];

    return ErrorCode::ERROR_SUCCESS;
}

void FileReaderApp::helpDisplay()
{
    std::cout << "Usage: " <<
            "FileReader.exe code-method file-path number-of-lines\n\n" <<
            "\tcode-method:\t\tSelect which method of file reading will be used.\n" <<
            "\t\t\t\t0: C code will be used\n\t\t\t\t1: C++ code will be used\n\n" <<
            "\tfile-path:\t\tPath to the file to read.\n" <<
            "\tnumber-of-lines:\tNumber of lines to read from the file.\n";
}

ErrorCode FileReaderApp::prepare()
{
    try
    {
        if(METHOD_C == codeMethod)
        {
            fileReader = new FileReaderC(filePath);
        }

        if(METHOD_CPP == codeMethod)
        {
            fileReader = new FileReaderCpp(filePath);
        }
    }
    catch (FileReaderException e)
    {
        if(FileReaderException::FILE_ACCESS_ERROR == e)
        {
            std::cout << "ERROR: Cannot access the file provided in path." << std::endl;
            std::cout << "Make sure path to file is valid, have permissions to read the file\nand it is not currently used by another program." << std::endl;
            return  ErrorCode::ERROR_FAIL;
        }
        if(FileReaderException::MEMORY_ERROR == e)
        {
            std::cout << "ERROR: Cannot allocate memory for program to use." << std::endl;
            return ErrorCode::ERROR_NOMEM;
        }
    }

    return ErrorCode::ERROR_SUCCESS;
}

ErrorCode FileReaderApp::process()
{
    int lineNum;
    std::optional<std::string> output;

    for(lineNum = 0; lineNum < numOfLines; lineNum++)
    {
        try
        {
            output = fileReader->readLine();
        }
        catch (FileReaderException e)
        {
            if(FileReaderException::MEMORY_ERROR == e)
            {
                std::cout << "ERROR: Cannot allocate memory for program to use." << std::endl;
                return ErrorCode::ERROR_NOMEM;
            }
        }

        if(!output.has_value())
        {
            break;
        }
        std::cout << output.value() << std::endl;
    }

    return ErrorCode::ERROR_SUCCESS;
}