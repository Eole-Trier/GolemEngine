#include "Debug/log.h"
#include <iostream>
#include <cstdarg>

std::fstream Log::mFile;

Log::~Log()
{
    mFile.close();
}

void Log::OpenFile(std::filesystem::path const& filename)
{
    mFile.open(filename, std::fstream::out);

    if (mFile.is_open())
    {
        std::cout << "Open file: " << filename << std::endl;
    }
    else 
        std::cout << "Cannot open the file: " << filename << std::endl;
}

void Log::Print(const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
        
    vsprintf_s(buffer, sizeof(buffer), format, args);
    std::cout << buffer << std::endl;

    if (mFile.is_open())
    {
        mFile << buffer << std::endl;
        mFile.flush();
    }
    
    va_end(args);
}
