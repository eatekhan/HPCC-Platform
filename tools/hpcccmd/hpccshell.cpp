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

    // while(args.isValid())
    // {
    //     if(args.matchFlag(boolFlag, "--help") && argc==4) // print out the req and res structure
    //     {
    //         if(boolFlag && argc==4)
    //         {
    //             myobj.esdlDefInit(argv[1], argv[2]);
    //             return;
    //         }
    //     }
    //     else if(args.matchFlag(boolFlag, "--printServices")) // helper for auto complete
    //     {
    //         if(boolFlag)
    //         {
               
    //             myobj.printAllServices();
    //             return;
    //         }
    //     }
    //     else if(args.matchFlag(boolFlag, "--printMethods")) // helper for auto complete
    //     {
    //         if(boolFlag)
    //         {
    //             if(argc < 3)
    //             {
    //                 std::cout << "Illegal Syntax" << std::endl;
    //                 return;
    //             }
               
    //             myobj.printAllMethods(argv[1]);
    //         }
    //     }
    //     else if(args.matchOption(value, "--formRequest") && argc == 4) // call method using form format (default json format)
    //     {
    //         if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = ".json";
    //             const char* reqType = "form";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         }
    //         else
    //         {
    //             std::cout << "Invalid Service/Method" << std::endl;
    //             return;
    //         }
    //     }
    //     else if(args.matchOption(value, "--formRequest") && argc ==5) // call method using form format (set res type)
    //     {
    //         if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = argv[4];
    //             const char* reqType = "form";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         }
    //         else
    //         {
    //             std::cout << "Invalid Service/Method" << std::endl;
    //             return;
    //         }
    //     }
    //     else if(args.matchOption(value, "--jsonRequest") && argc ==4)
    //     {
    //         if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = ".json";
    //             const char* reqType = "json";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         } 
    //         else
    //         {
    //             std::cout << "Invalid Service/Method" << std::endl;
    //             return;
    //         }
    //         // std::cout << value << std::endl;
    //     }
    //     else if(args.matchOption(value, "--xmlRequest") && argc ==4)
    //     {
    //         if(myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]))
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = ".xml";
    //             const char* reqType = "xml";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         } 
    //         else
    //         {
    //             std::cout << "Invalid Service/Method" << std::endl;
    //             return;
    //         }
    //         // std::cout << value << std::endl;
    //     }
    //     else if(args.matchFlag(value, "--test"))
    //     {
    //         std::cout << value << std::endl;
    //     }
    //     args.next();
    // }

    // bool isValidServiceAndMethod = argc > 3 && myobj.checkValidService(argv[1]) && myobj.checkValidMethod(argv[2], argv[1]);
    // while(args.isValid())
    // {
    //     bool boolFlag;
    //     StringAttr value;
        
    //     if(args.matchFlag(boolFlag, "--printServices"))
    //     {
    //         myobj.printAllServices();
    //         return;
    //     }

    //     if(args.matchFlag(boolFlag, "--printMethods")) // helper for auto complete
    //     { 
    //         if(argc != 3)
    //         {
    //             std::cout << "Illegal Syntax" << std::endl;
    //             printHelp();
    //             return;
    //         }
    //         myobj.printAllMethods(argv[1]);
    //         return;
    //     }

    //     if(isValidServiceAndMethod)
    //     {
    //         if(args.matchFlag(boolFlag, "--help"))
    //         {
    //             myobj.esdlDefInit(argv[1], argv[2]);
    //             return;
    //         }
    //         if(args.matchOption(value, "--formRequest") && argc == 4)
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = ".json"; //Default response type for forms
    //             const char* reqType = "form";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         }

    //         // else if(args.matchOption(value, "--formRequest") && argc == 4)
    //         // {
    //         //     const char* formArgs = value.str();
    //         //     const char* resType = ".json"; //Default response type for forms
    //         //     const char* reqType = "form";
    //         //     hpccService myServ(argc, argv, formArgs, resType, reqType);
    //         //     return;
    //         // }

    //         if(args.matchOption(value, "--formRequest") && argc == 5)
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = argv[4];
    //             const char* reqType = "form";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         }



    //         if(args.matchOption(value, "--jsonRequest"))
    //         {
    //             if(argc==7)
    //             {
    //                bool targetFound = false, userFound = false, passFound = false; 
    //                StringAttr targeturl, username, password;
    //                args.first();
    //                while (args.isValid()) 
    //                {
    //                     if (args.matchOption(targeturl, "-t")) {
    //                         targetFound = true;
    //                     } else if (args.matchOption(username, "-u")) {
    //                         userFound = true;
    //                     } else if (args.matchOption(password, "-p")) {
    //                         passFound = true;
    //                     }
    //                     args.next();
    //                 }
    //                 if (targetFound && userFound && passFound) 
    //                 {
    //                         const char* formArgs = value.str();
    //                         const char* resType = ".json";
    //                         const char* reqType = "json";
    //                         const char* target = targeturl.str();
    //                         const char* user = username.str();
    //                         const char* pass = password.str();
    //                         std::cout << user << "work" << std::endl;
    //                         std::cout << pass << "work" << std::endl;

    //                         // Assuming hpccService can accept user and pass
    //                         hpccService myServ(argc, argv, formArgs, resType, reqType, target,user, pass);
    //                         return;
    //                 } 
    //                 else
    //                 {
    //                         std::cout << "Username or password not provided." << std::endl;
    //                 }

    //             }

    //             const char* formArgs = value.str();
    //             const char* resType = ".json";
    //             const char* reqType = "json";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         }




    //         else if(args.matchOption(value, "--xmlRequest") && argc ==4)
    //         {
    //             const char* formArgs = value.str();
    //             const char* resType = ".xml";
    //             const char* reqType = "xml";
    //             hpccService myServ(argc, argv, formArgs, resType, reqType);
    //             return;
    //         }

    //     }




    //     args.next();
    // }


    bool hasServiceName=false, hasMethodName=false, hasDescribe=false;
    bool hasPrintService = false, hasPrintMethod = false;
    bool hasTarget = false, hasRequestType = false, hasResponseType = false;

    StringAttr requestType, responseType, target;

    bool hasUsername = false, hasPassword = false, hasReqStr = false;
    StringAttr username, password;
    StringAttr reqStr;
    while(args.isValid())
    {
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
        cout << args.query() << endl;
        if(args.matchOption(target,"--target"))
        {
            hasTarget = true;
            args.next();
            // std::cout << target << std::endl;
            continue;
        }
        if(args.matchOption(requestType, "--reqType"))
        {
            cout << requestType;
            hasRequestType = true;
            args.next();
            // std::cout << requestType << std::endl;
            continue;
        }
        if(args.matchOption(reqStr, "--reqStr"))
        {
            hasReqStr = true;
            args.next();
            // std::cout << reqStr << std::endl;
            continue;
        }
        if(args.matchOption(responseType, "--resType"))
        {
            hasResponseType = true;
            args.next();
            // std::cout << reqStr << std::endl;
            continue;
        }

        args.next();
    }
    //////////////////////////////////////////////////////////////////////////////////////////
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
        if(strcmp(requestType, "json")==0)
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
            hpccService myServ(argc, argv, formArgs, resType, reqType, targeturl);
            return;
        }
        else if(strcmp(requestType, "xml")==0)
        {
            if(!hasReqStr)
            {
                std::cout << "request string not provided" << std::endl;
            }
            cout << "INSIDE XML" << endl;
            const char* formArgs = reqStr.str();
            const char* resType = ".xml";
            const char* reqType = "xml";
            hpccService myServ(argc, argv, formArgs, resType, reqType);
            return;
        }
        else if(strcmp(requestType, "form")==0)
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
           
            hpccService myServ(argc, argv, formArgs, resType, reqType);
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