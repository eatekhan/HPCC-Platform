#include <cstring>
#include <iostream>
#include "esdl_def.hpp"
#include "jargv.hpp"
#include "jprop.hpp"
#include "esdl_def.hpp"
#include "esdl_def_helper.hpp"
#include "jstring.hpp"
#include "hpccshell.hpp"
#include <vector>
#include <stdio.h>
#include "thorplugin.hpp"

using namespace std;
//#include "../../esp/esdllib"

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

void getAllMethods(Owned<IEsdlDefinition> &esdlDef, const char* serviceName, const char* methodName)
{
    auto *esdlServ = esdlDef->queryService(serviceName); // WsTopology
    auto *methodIter = esdlServ->getMethods();
    methodIter->first();
    for(;methodIter->isValid();methodIter->next())
    {
        auto &tempMethod =  methodIter->query();
        //strcmp(tempMethod.queryName(), methodName)
        const char* tempMethodQueryName = tempMethod.queryName();
        if(strcmp(tempMethod.queryName(), methodName) == 0)
        {
            traverseProps(esdlDef, tempMethod.queryRequestType());
        }
    }
}

void esdlDefInit(Owned<IEsdlDefinition> esdlDef, const char* serviceName, const char* methodName)
{
    Owned<IFile> serviceDefFile;
    // Owned<IEsdlDefinition> esdlDef;
    // Owned<IEsdlDefinitionHelper> defHelper;


    // esdlDef.set(createEsdlDefinition(nullptr, createConcreteEsdlDefReporter));
    // defHelper.setown(createEsdlDefinitionHelper());
    // IEsdlDefReporter* reporter = esdlDef->queryReporter();
    // IEsdlDefReporter::Flags traceFlags = IEsdlDefReporter::ReportErrorClass;


    serviceDefFile.setown( createIFile("/home/khan/HPCC-Platform/tools/hpcccmd/ws_topology.xml")); // include path
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
    // getAllMethods(esdlDef, "WsTopologyy", "TpMachineQuery");
}



vector<const char*> getFileNames()
{
    const char * mask = "*" ".xml";
    vector<const char*> fileNamesVector;

    Owned<IFile> esdlDir = createIFile("/opt/HPCCSystems/componentfiles/esdl_files/");
    Owned<IDirectoryIterator> esdlFiles = esdlDir->directoryFiles(mask,false,false);
    ForEach(*esdlFiles)
    {
        const char *thisPlugin = esdlFiles->query().queryFilename();
        StringBuffer path;
        StringBuffer tail;
        cout << thisPlugin << endl;
        fileNamesVector.push_back(path);
    }
    return fileNamesVector;
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
    IEsdlDefReporter::Flags traceFlags = IEsdlDefReporter::ReportErrorClass;



    if(args.matchOption(methodName,"WsTopology"))
    {
        const char* serviceName = args.query();
        const char* methodName = methodName;
        esdlDefInit(esdlDef, serviceName, methodName)
    }
    if(args.matchOption(methodName,"WSDali"))
    {
        
    }

    return 0;
}