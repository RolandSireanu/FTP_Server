#ifndef MKDIR_COMMAND_H
#define MKDIR_COMMAND_H

#include <CommandProcessor.h>

class MkdirHandler : public BaseHandler
{
    public:
        virtual bool Handle(std::string arg_request);
};

#endif