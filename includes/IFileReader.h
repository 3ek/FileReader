#ifndef IFILEREADER_H
#define IFILEREADER_H
#include <optional>

enum FileReaderException
{
    FILE_ACCESS_ERROR = 0xABBA,
};

class IFileReader
{
public:
    IFileReader(){}
    virtual ~IFileReader(){}
    virtual std::optional<std::string> readLine() = 0;
};

#endif // IFILEREADER_H
