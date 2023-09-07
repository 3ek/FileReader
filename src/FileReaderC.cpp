#include <errno.h>
#include <iostream>
#include <cstdio>
#include <optional>
#include <string>
#include "FileReaderC.hpp"

FileReaderC::FileReaderC(char* filePath)
{
    errno_t status;
    status = fopen_s(&pF, filePath, "rb");

    if((0 != status) || (nullptr == pF))
    {
        throw FileReaderException::FILE_ACCESS_ERROR;
    }

    strBuf = malloc(0);
    if(nullptr == strBuf)
    {
        throw FileReaderException::MEMORY_ERROR;
    }
}

FileReaderC::~FileReaderC()
{
    free(strBuf);
    if(nullptr != pF)
    {
        fclose(pF);
    }
}

std::optional<std::string> FileReaderC::readLine()
{
    ErrorCode status;
    void * retval;
    std::string retstr;

    if(feof(pF) || isEof)
    {
        return std::nullopt;
    }

    status = setBuffer();
    retval = fgets((char*)strBuf, strBufSize, pF);

    if((nullptr == retval) || (ErrorCode::ERROR_SUCCESS != status))
    {
        return std::nullopt;
    }

    return retstr.assign((char*)strBuf);
}

ErrorCode FileReaderC::getNextEol(int * nextEolPos, bool * isCrPresent)
{
    int newPos = currPos;
    int getChar = getc(pF);

    if(nullptr == isCrPresent)
    {
        return ErrorCode::ERROR_INVALID_PTR;
    }

    fseek(pF, currPos, SEEK_SET);
    while(!feof(pF) && !isEof)
    {
        getChar = getc(pF);
        newPos++;
        if(getChar == '\r')
        {
            *isCrPresent = true;
        }
        if(getChar == -1)
        {
            isEof = true;
        }
        if(feof(pF) || (getChar == '\n'))
        {
            break;
        }
    }

    if(*isCrPresent)
    {
        newPos--;
    }
    fseek(pF, currPos, SEEK_SET); // Revert position

    if(newPos < currPos)
    {
        return ErrorCode::ERROR_FAIL;
    }

    *nextEolPos = newPos;

    return ErrorCode::ERROR_SUCCESS;
}

ErrorCode FileReaderC::setBuffer()
{
    ErrorCode status;
    int newPos = 0;
    bool isCrPresent = false;

    status = getNextEol(&newPos, &isCrPresent);
    if(ErrorCode::ERROR_SUCCESS != status)
    {
        return status;
    }

    strBufSize = newPos - currPos;
    strBuf = realloc(strBuf, strBufSize);

    if(nullptr == strBuf)
    {
        throw FileReaderException::MEMORY_ERROR;
    }

    currPos = newPos + (int)isCrPresent;

    return ErrorCode::ERROR_SUCCESS;
}