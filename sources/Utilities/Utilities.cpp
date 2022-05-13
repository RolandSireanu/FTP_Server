#include "Utilities.h"

std::size_t extractPathSize(const char* arg_req, std::size_t arg_startPos)
{
    std::size_t i = arg_startPos;
    std::size_t sizeOfPath = 0;
    while(arg_req[i] >= '0' && arg_req[i] <= '9')
    {
        sizeOfPath = (sizeOfPath*10) + (arg_req[i] - 48);
        i++;
    }

    return sizeOfPath > 0 ? sizeOfPath : -1;
}


void createPath(char* arg_path, const char* arg_startingPath)
{
    constexpr std::size_t MAX_PATH_LENGTH = 1024;
    char finalPath[MAX_PATH_LENGTH];
    char* ptr = strtok(arg_path, "/");
    std::size_t counter = 0;
    
    memset(finalPath, 0, MAX_PATH_LENGTH/4);
    strcat(finalPath, arg_startingPath);
    strcat(finalPath, "/");

    while(ptr != NULL)
    {
        strcat(finalPath, ptr);
        strcat(finalPath, "/");

        if(std::filesystem::exists(finalPath) == false)
        {
            std::filesystem::create_directory(finalPath);    
        }
        ptr = strtok(NULL, "/");
    }
}