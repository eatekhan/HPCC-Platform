// #include "hpcccmd.hpp"
#include "jargv.hpp"
#include "jstring.hpp"
#include "hpccshell.hpp"
#include "jargv.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "hpccservice.hpp"


using namespace std;
void hpccShell::printHelp()
{
    fprintf(stdout,"\nUsage:\n"
        "    hpcc <ServiceName> <MethodName> [commands]\n\n"
        "List of Available commands\n"
           
           "   --describe                                        Print out the request and response structure for the method.\n"
           "   --reqStr <XML or JSON or Form request string>     Send request to the method in xml or json format.\n"
           "   --resTypeForm <xml || json>                       Send the response type for the form request.\n"
           "   --target                                          Set the target url for the esp server.\n"
           "   -u, --username <username>                         Set the username for authentication.\n"
           "   -p, --password <password>                         Set the password for authentication.\n"
           "\n"

           "   Example: WsWorkunits WUDelete --target http://127.0.0.1:8010/ --reqStr {WUDeleteRequest:{Wuids:{Item:[test]},BlockTillFinishTimer:0}} -p changeme -u Eatesam\n "
           "\n" 
           "   hpcc --printServices\n"
           "   hpcc <ServiceName> --printMethods\n"
           ""
           "\nRun 'hpcc <tab>' to display list of services\n"
           "\nRun 'hpcc <ServiceName> <tab>' to display list of methods\n\n"
    );
}
void hpccShell::parseCmdOptions(hpccInit &myobj, int argc, const char* argv[])
{
    bool boolFlag;
    StringAttr value;

    bool hasValidService=false, hasValidMethod=false, hasDescribe=false;
    bool hasPrintService = false, hasPrintMethod = false, hasHelp=false;
    bool hasTarget = false, hasRequestType = false, hasResponseType = false;

    const char* serviceName;
    const char* methodName;

    StringAttr requestType, responseType, target;

    bool hasUsername = false, hasPassword = false, hasReqStr = false;
    StringAttr username, password;
    StringAttr reqStr;
    while(args.isValid())
    {
        if(args.matchFlag(hasHelp, "--help"))
        {
            hasHelp = true;
            break;
        }
        if(args.matchFlag(hasPrintService, "--printServices"))
        {
            break;
        }
        if(args.matchFlag(hasPrintMethod, "--printMethods"))
        {
            break;
        }
        if(args.matchFlag(hasDescribe, "--describe"))
        {
            break;
        }
        if(args.matchOption(target,"--target"))
        {
            hasTarget = true;
            args.next();
            continue;
        }
        if(args.matchOption(requestType, "--reqType"))
        {
            cout << requestType;
            hasRequestType = true;
            args.next();
            continue;
        }
        if(args.matchOption(reqStr, "--reqStr"))
        {
            hasReqStr = true;
            args.next();
            continue;
        }
        if(args.matchOption(responseType, "--resTypeForm"))
        {
            hasResponseType = true;
            args.next();
            continue;
        }
        if(args.matchOption(username, "-u") || args.matchOption(username, "--username"))
        {
            hasUsername = true;
            args.next();
            continue;
        }
        if(args.matchOption(password, "-p") || args.matchOption(password, "--password"))
        {
            hasPassword = true;
            args.next();
            continue;
        }

        args.next();
    }
    //////////////////////////////////////////////////////////////////////////////////////////

    if(hasHelp)
    {
        printHelp();
        return;
    }
    if(hasPrintService)
    {
        myobj.printAllServices();
        return;   
    }

    if(hasPrintMethod)
    {
        if(argc < 3)
        {
            std::cout << "Illegal Syntax, Enter a Valid Service Name" << std::endl;
            return;
        }
        myobj.printAllMethods(argv[1]); //argv[1] is the service name
        return;
    }

    bool isValidServiceAndMethod = argc > 3 && myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]);
    if(isValidServiceAndMethod)
    {
        hasValidMethod = true;
        hasValidService = true;
        serviceName = argv[1];
        methodName = argv[2];
    }

    if(isValidServiceAndMethod)
    {
        if(hasDescribe)
        {
            myobj.esdlDefInit(serviceName, methodName);
            return;
        }
        if(hasReqStr && reqStr[0] == '{')
        {
            if(!hasReqStr)
            {
                std::cout << "request string not provided" << std::endl;
            }
            cout << "INSIDE JSON" << endl;
            const char* formArgs = reqStr.str();
            const char* resType = ".json";
            const char* reqType = "json";
            const char* targeturl = target.str();

            if(hasUsername && hasPassword)
            {
                hpccService myServ(serviceName, methodName, formArgs, resType, reqType, targeturl, username.str(), password.str());
                return;
            }
            hpccService myServ(serviceName, methodName, formArgs, resType, reqType, targeturl);
            return;
        }
        else if(hasReqStr && reqStr[0] == '<')
        {
            if(!hasReqStr)
            {
                std::cout << "request string not provided" << std::endl;
            }
            cout << "INSIDE XML" << endl;
            const char* formArgs = reqStr.str();
            const char* resType = ".xml";
            const char* reqType = "xml";
            const char* targeturl = target.str();


            if(hasUsername && hasPassword)
            {
                hpccService myServ(serviceName, methodName, formArgs, resType, reqType, targeturl, username.str(), password.str());
                return;
            }
            hpccService myServ(serviceName, methodName, formArgs, resType, reqType, targeturl);
            
            return;
        }
        else// FORM REQUEST
        {
            if(!hasReqStr)
            {
                std::cout << "request string not provided" << std::endl;
            }
            cout << "INSIDE FORM" << endl;
            const char* formArgs = reqStr.str();
            const char* resType = ".json";
            if(hasResponseType)
            {
                resType = (strcmp(responseType, "xml")==0) ? ".xml" : ".json";
            }
           
            const char* reqType = "form";
            const char* targeturl = target.str();


            if(hasUsername && hasPassword)
            {
                hpccService myServ(serviceName, methodName, formArgs, resType, reqType, targeturl, username.str(), password.str());
                return;
            }
            hpccService myServ(serviceName, methodName, formArgs, resType, reqType, targeturl);
           
            return;
        } 
    }
    else
    {
        std::cout << "Not a Valid Service and Method" << std::endl;
    }
    printHelp();
}

hpccShell::hpccShell(int argc, const char* argv[]) : args(argc, argv)
{
    hpccInit myobj;


    parseCmdOptions(myobj, argc, argv);
}