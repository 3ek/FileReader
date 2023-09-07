#include "Common.hpp"
#include "FileReaderApp.hpp"

int main(int argc, char** argv)
{
    int status = 0;
    FileReaderApp* reader;

    try
    {
        reader = FileReaderApp::instance(argc, argv);
        reader->process();
    }
    catch(ErrorCode e)
    {
        status = static_cast<int>(e);
    }

    reader->release();
    return status;
}
