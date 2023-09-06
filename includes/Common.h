#ifndef COMMON_H
#define COMMON_H

enum ErrorCode
{
    ERROR_SUCCESS,
    ERROR_FAIL,
    ERROR_INVARGS,
    ERROR_INVALID_PTR
};

enum ReadMethods
{
    METHOD_C,
    METHOD_CPP,
    METHOD_MAX
};

#endif // COMMON_H
