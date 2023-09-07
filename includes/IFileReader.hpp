#ifndef IFILEREADER_HPP
#define IFILEREADER_HPP
#include <optional>
#include <string>

enum class FileReaderException
{
    FILE_ACCESS_ERROR = 0xABBA,
    MEMORY_ERROR,
};

class IFileReader
{
public:
    IFileReader(){}
    virtual ~IFileReader(){}
    virtual std::optional<std::string> readLine() = 0;
};

#endif // IFILEREADER_HPP
