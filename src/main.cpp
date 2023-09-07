#include <iostream>
#include "Common.hpp"
#include "IFileReader.hpp"
#include "FileReaderC.hpp"
#include "FileReaderCpp.hpp"

#define REQ_ARG_NUM 4

void helpDisplay(void)
{
    std::cout << "Usage: " <<
            "FileReader.exe code-method file-path number-of-lines\n\n" <<
            "\tcode-method:\t\tSelect which method of file reading will be used.\n" <<
            "\t\t\t\t0: C code will be used\n\t\t\t\t1: C++ code will be used\n\n" <<
            "\tfile-path:\t\tPath to the file to read.\n" <<
            "\tnumber-of-lines:\tNumber of lines to read from the file.\n";
}

ErrorCode checkArgs(int argc, char** argv, int* codeMethod, char** filePath, int* numOfLines)
{
    if(REQ_ARG_NUM != argc)
    {
        helpDisplay();
        return ERROR_INVARGS;
    }
    
    try
    {
        *codeMethod = std::stoi(argv[1], nullptr);
    }
    catch (...)
    {
        std::cout << "Invalid value in code-method." << std::endl;
        helpDisplay();
        return ERROR_INVARGS;
    }
    
    if(*codeMethod >= METHOD_MAX)
    {
        std::cout << "Value out of range in code-method." << std::endl;
        helpDisplay();
        return ERROR_INVARGS;
    }
       
    try
    {
        *numOfLines = std::stoi(argv[3], nullptr);
    }
    catch (...)
    {
        std::cout << "Invalid value in number-of-lines." << std::endl;
        helpDisplay();
        return ERROR_INVARGS;
    } 
    
    if(0 > *numOfLines)
    {
        std::cout << "Value out of range in number-of-lines." << std::endl;
        helpDisplay();
        return ERROR_INVARGS;
    }
    
    *filePath = argv[2]; // TODO: Validation?
    
    return ERROR_SUCCESS;
}

int main(int argc, char** argv)
{
    ErrorCode status;
    std::string helpStr ("--help");
    IFileReader *fileReader {nullptr};
    int codeMethod;
    char* filePath;
    int numOfLines;
    std::optional<std::string> output;
    int lineNum = 0;
    
    if((2 == argc) && (0 == helpStr.compare(argv[1])))
    {
        helpDisplay();
        return 0;
    }
    
    status = checkArgs(argc, argv, &codeMethod, &filePath, &numOfLines);
    if(ERROR_SUCCESS != status)
    {
        return status;
    }
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
    catch (FileReaderException FILE_ACCESS_ERROR)
    {
        std::cout << "Cannot access the file provided in path." << std::endl;
        std::cout << "Make sure path to file is valid, have permissions to read the file\nand it is not currently used by another program." << std::endl;
        return ERROR_FAIL;
    }

    for(lineNum = 0; lineNum < numOfLines; lineNum++)
    {
        output = fileReader->readLine();
        if(!output.has_value())
        {
            break;
        }
        std::cout << output.value() << std::endl;
    }
    
    delete fileReader;
    return 0;
}