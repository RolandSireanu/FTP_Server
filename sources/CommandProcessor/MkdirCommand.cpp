#include <MkdirCommand.h>
#include <iostream>


// class MkdirHandler : public BaseHandler
// {
//     public:
//         bool Handle(std::string arg_request);
// };


bool MkdirHandler::Handle(std::string arg_request)
{
    std::cout << "MkdirHandler not suitable, forward request ..." << std::endl;
    return BaseHandler::Handle(arg_request);
}