#include <cstring>
#include <iostream>
#include "esdl_def.hpp"
#include "jargv.hpp"
#include "jprop.hpp"
#include "esdl_def.hpp"
#include "esdl_def_helper.hpp"
#include "jstring.hpp"
#include "hpccshell.hpp"
#include <string>
#include <vector>
#include <stdio.h>
#include "thorplugin.hpp"

using namespace std;
class ConcreteEsdlDefReporter : public EsdlDefReporter
{
protected:
    void reportSelf(Flags flags, const char* component, const char* level, const char* msg) const override
    {
        printf("[%s] [%s] %s\n", component, level, msg);
    }
};


IEsdlDefReporter* createConcreteEsdlDefReporter()
{
    return new ConcreteEsdlDefReporter();
}



void traverseProps(Owned<IEsdlDefinition> &esdlDef, const char* reqRes)
{
    // "TpSetMachineStatusRequest"
    auto myStruct = esdlDef->queryStruct(reqRes);
    cout << myStruct->queryName() <<endl;

    auto structChildren = myStruct->getChildren();
    structChildren->first() ;

    for(;structChildren->isValid();structChildren->next())
    {
        auto &tempQuery = structChildren->query();
        //cout << tempQuery.queryName() << endl;
        auto *tempQueryProps = tempQuery.getProps();
        tempQueryProps->first();
        for(;tempQueryProps->isValid();tempQueryProps->next())
        {
            cout << tempQueryProps->getPropKey() << " " << tempQueryProps->queryPropValue() << endl;
        }
    }
}

void getAllMethods(Owned<IEsdlDefinition> &esdlDef, const char* serviceName, const char* methodName, bool &flagSuccess)
{
    auto *esdlServ = esdlDef->queryService(serviceName); 
    if (!esdlServ)
    {
        std::cerr << "Service not found: " << serviceName << std::endl;
        return;
    }

    try {
        auto *methodIter = esdlServ->getMethods();
        if (!methodIter)
        {
            std::cerr << "No methods found for service: " << serviceName << std::endl;
            return;
        }

        for (methodIter->first(); methodIter->isValid(); methodIter->next())
        {
            auto &tempMethod = methodIter->query();
            if (strcmp(tempMethod.queryName(), methodName) == 0)
            {
                traverseProps(esdlDef, tempMethod.queryRequestType());
                flagSuccess = true;
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught an unknown exception!" << std::endl;
    }
}


void getFileNames(vector<string> &methodsList)
{
    const char * mask = "*" ".xml";
    //vector<const char*> fileNamesVector;

    Owned<IFile> esdlDir = createIFile("/opt/HPCCSystems/componentfiles/esdl_files/");
    Owned<IDirectoryIterator> esdlFiles = esdlDir->directoryFiles(mask,false,false);
    ForEach(*esdlFiles)
    {
        const char *thisPlugin = esdlFiles->query().queryFilename();
       // cout << thisPlugin << endl;
        methodsList.push_back(thisPlugin);
    }
    return;
} 


void esdlDefInit(Owned<IEsdlDefinition> esdlDef, const char* serviceName, const char* methodName)
{
    Owned<IFile> serviceDefFile;

    vector<string> fileList;
    getFileNames(fileList);
    for(const auto& file: fileList)
    {
        cout << file << endl;
        const char* fileNameChar = file.c_str();
    
        serviceDefFile.setown( createIFile(fileNameChar));


        if(serviceDefFile->exists())
        {
            if( serviceDefFile->size() > 0 )
            {
                esdlDef->addDefinitionsFromFile( serviceDefFile->queryFilename() );
            }
        }
        else
        {
            throw( MakeStringException(0, "ESDL definition file source %s is not a file", "sourceFileName") );
        }
        bool flagSuccess = false;
        getAllMethods(esdlDef, serviceName, methodName, flagSuccess);
        if(flagSuccess)
        {
            break;
        }
    }
  
}





int main(int argc, const char* argv[])
{
    InitModuleObjects();
    // getFileNames();
    // esdlDefInit();
    // hpccShell myShell(argc, argv);
    ArgvIterator args(argc, argv);
    StringAttr methodName;
    bool help;


    Owned<IEsdlDefinition> esdlDef;
    Owned<IEsdlDefinitionHelper> defHelper;


    esdlDef.set(createEsdlDefinition(nullptr, createConcreteEsdlDefReporter));
    defHelper.setown(createEsdlDefinitionHelper());
    IEsdlDefReporter* reporter = esdlDef->queryReporter();
    //reporter->setFlags(Flags flags, bool state)
    IEsdlDefReporter::Flags traceFlags = IEsdlDefReporter::ReportErrorClass;



    if(args.matchOption(methodName,"WsTopology"))
    {
        const char* serviceName = args.query();
        const char* methodName = methodName;
        esdlDefInit(esdlDef, "WsWorkunits", "WUAbort");
    }
    if(args.matchOption(methodName,"WSDali"))
    {
        
    }

    return 0;
}