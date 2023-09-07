#include <iostream>
#include <cstdio>
#include <optional>
#include "FileReaderC.hpp"

FileReaderC::FileReaderC(char* filePath) //TODO: Issues using fgets with dynamic buffer between Windows and Linux file format.
{
    pF = fopen(filePath, "rb");
    if(nullptr == pF)
    {
        throw FILE_ACCESS_ERROR;
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
    
    if((nullptr == retval) || (ERROR_SUCCESS != status))
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
        return ERROR_INVALID_PTR;
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
        return ERROR_FAIL;
    }
    
    *nextEolPos = newPos;
    
    return ERROR_SUCCESS;
}

ErrorCode FileReaderC::setBuffer()
{
    ErrorCode status;
    int newPos = 0;
    bool isCrPresent = false;
    
    status = getNextEol(&newPos, &isCrPresent);
    if(ERROR_SUCCESS != status)
    {
        return status;
    }
    
    strBufSize = newPos - currPos;
    strBuf = realloc(strBuf, strBufSize);
    
    if(nullptr == strBuf)
    {
        return ERROR_FAIL;
    }
    
    currPos = newPos + (int)isCrPresent;
    
    return ERROR_SUCCESS;
}