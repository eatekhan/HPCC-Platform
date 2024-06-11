// #include "hpcccmd.hpp"
#include "jargv.hpp"
#include "jstring.hpp"
#include "hpccshell.hpp"
#include "jargv.hpp"
#include <iostream>



void hpccShell::parseCmdOptions(hpccInit &myobj, int argc, const char* argv[])
{
    bool boolFlag;
    while(args.isValid())
    {
        if(args.matchFlag(boolFlag, "--help"))
        {
            if(boolFlag && argc==4)
            {
                myobj.esdlDefInit(argv[1], argv[2]);
            }
        }
        if(args.matchFlag(boolFlag, "--printServices"))
        {
            if(boolFlag)
            {
               
                myobj.printAllServices();
            }
        }
        if(args.matchFlag(boolFlag, "--printMethods"))
        {
            if(boolFlag)
            {
                if(argc < 3)
                {
                    std::cout << "Illegal Syntax" << std::endl;
                    return;
                }
               
                myobj.printAllMethods(argv[1]);
            }
        }
        args.next();
    }
}

hpccShell::hpccShell(int argc, const char* argv[]) : args(argc, argv)
{
    hpccInit myobj;


    parseCmdOptions(myobj, argc, argv);
}