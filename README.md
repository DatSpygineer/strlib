# Str-lib
A general purpose string class, extending std::string with fmt lib integration.

The purpose of this library is to expand the standard string with extra functionality,
with a more modern formatting function.

This library also adds extra file system extension.

Can be disabled by setting CMake variable:
```cmake
set(STRLIB_FILESYS OFF)
```

Built with C++ 20, compatible with C++ 17.

### Dependencies:

* fmtlib - https://github.com/fmtlib/fmt