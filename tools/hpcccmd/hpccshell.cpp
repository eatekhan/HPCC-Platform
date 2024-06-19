// #include "hpcccmd.hpp"
#include "jargv.hpp"
#include "jstring.hpp"
#include "hpccshell.hpp"
#include "jargv.hpp"
#include <cstdio>
#include <iostream>
#include "hpccservice.hpp"



void hpccShell::printHelp()
{
    fprintf(stdout,"\nUsage:\n"
        "    hpcc <ServiceName> <MethodName> [commands]\n\n"
        "List of Available commands\n"
           "   --help                      Print out the request and response structure for the method.\n"
           "   --jsonRequest=<rawJson>     Send request to the method in json format.  \n"
           "   --formRequest=<queryString> Send request to the method in form format.\n"
           "   --xmlRequest=<rawXML>       Send request to the method in xml format.\n"
           ""
           "\nRun 'hpcc <tab>' to display list of services\n"
           "\nRun 'hpcc <ServiceName> <tab>' to display list of methods\n\n"
    );
}
void hpccShell::parseCmdOptions(hpccInit &myobj, int argc, const char* argv[])
{
    bool boolFlag;
    StringAttr value;
    while(args.isValid())
    {
        if(args.matchFlag(boolFlag, "--help") && argc==4) // print out the req and res structure
        {
            if(boolFlag && argc==4)
            {
                myobj.esdlDefInit(argv[1], argv[2]);
                return;
            }
        }
        else if(args.matchFlag(boolFlag, "--printServices")) // helper for auto complete
        {
            if(boolFlag)
            {
               
                myobj.printAllServices();
                return;
            }
        }
        else if(args.matchFlag(boolFlag, "--printMethods")) // helper for auto complete
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
        else if(args.matchOption(value, "--formRequest") && argc == 4) // call method using form format (default json format)
        {
            if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
            {
                const char* formArgs = value.str();
                const char* resType = ".json";
                const char* reqType = "form";
                hpccService myServ(argc, argv, formArgs, resType, reqType);
                return;
            }
            else
            {
                std::cout << "Invalid Service/Method" << std::endl;
                return;
            }
        }
        else if(args.matchOption(value, "--formRequest") && argc ==5) // call method using form format (set res type)
        {
            if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
            {
                const char* formArgs = value.str();
                const char* resType = argv[4];
                const char* reqType = "form";
                hpccService myServ(argc, argv, formArgs, resType, reqType);
                return;
            }
            else
            {
                std::cout << "Invalid Service/Method" << std::endl;
                return;
            }
        }
        else if(args.matchOption(value, "--jsonRequest") && argc ==4)
        {
            if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
            {
                const char* formArgs = value.str();
                const char* resType = ".json";
                const char* reqType = "json";
                hpccService myServ(argc, argv, formArgs, resType, reqType);
                return;
            } 
            else
            {
                std::cout << "Invalid Service/Method" << std::endl;
                return;
            }
            // std::cout << value << std::endl;
        }
        else if(args.matchOption(value, "--xmlRequest") && argc ==4)
        {
            if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
            {
                const char* formArgs = value.str();
                const char* resType = ".xml";
                const char* reqType = "xml";
                hpccService myServ(argc, argv, formArgs, resType, reqType);
                return;
            } 
            else
            {
                std::cout << "Invalid Service/Method" << std::endl;
                return;
            }
            // std::cout << value << std::endl;
        }
        else if(args.matchFlag(value, "--test"))
        {
            std::cout << value << std::endl;
        }
        args.next();
    }
    printHelp();
}

hpccShell::hpccShell(int argc, const char* argv[]) : args(argc, argv)
{
    hpccInit myobj;


    parseCmdOptions(myobj, argc, argv);
}