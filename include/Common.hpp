#ifndef COMMON_HPP
#define COMMON_HPP

enum class ErrorCode : int
{
    ERROR_SUCCESS,
    ERROR_FAIL,
    ERROR_INVARGS,
    ERROR_INVALID_PTR,
    ERROR_NOMEM
};

enum ReadMethods
{
    METHOD_C,
    METHOD_CPP,
    METHOD_MAX
};

#endif // COMMON_HPP
