#ifndef IFILEREADER_HPP
#define IFILEREADER_HPP
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

#endif // IFILEREADER_HPP
