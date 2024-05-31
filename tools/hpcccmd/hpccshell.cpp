#include <iostream>
#include "jargv.hpp"
#include "jstring.hpp"
#include "hpccshell.hpp"
#include "jargv.hpp"
using namespace std;

hpccShell::hpccShell(int argc, const char* argv[])
{
    
    auto arg = ArgvIterator(argc, argv);

    StringAttr methodName;
    bool help;


    if(arg.matchOption(methodName,"WsTopology"))
    {
        
    }
}