#include <cstring>
#include <iostream>
#include "esdl_def.hpp"
#include "jprop.hpp"
#include "esdl_def.hpp"
#include "esdl_def_helper.hpp"
#include "jstring.hpp"
#include <string>
#include <vector>
#include <stdio.h>
#include "hpcccmd.hpp"
#include "hpccshell.hpp"

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


hpccInit::hpccInit() {
    InitModuleObjects();
    queryStderrLogMsgHandler()->setMessageFields(0);
        
    esdlDef.set(createEsdlDefinition(nullptr, createConcreteEsdlDefReporter));
    defHelper.setown(createEsdlDefinitionHelper());
    IEsdlDefReporter* reporter = esdlDef->queryReporter();
    using TraceFlags = IEsdlDefReporter::Flags;
    
    TraceFlags traceFlags = IEsdlDefReporter::ReportDisaster;
    reporter->setFlags(traceFlags, true);

}

void hpccInit::getFileNames(vector<string> &methodsList) 
{
    const char * mask = "*" ".xml";
    Owned<IFile> esdlDir = createIFile("/opt/HPCCSystems/componentfiles/esdl_files/");
    
    Owned<IDirectoryIterator> esdlFiles = esdlDir->directoryFiles(mask, false, false);
    ForEach(*esdlFiles) 
    {
        const char *thisPlugin = esdlFiles->query().queryFilename();
        methodsList.push_back(thisPlugin);
    }
    return;
}

void hpccInit::traverseProps(const char* reqRes) 
{
    auto myStruct = esdlDef->queryStruct(reqRes);
    cout << myStruct->queryName() << endl;

    auto structChildren = myStruct->getChildren();
   

    for(structChildren->first();structChildren->isValid();structChildren->next()) 
    {
        auto &tempQuery = structChildren->query();
        auto *tempQueryProps = tempQuery.getProps();
        tempQueryProps->first();
        for(;tempQueryProps->isValid();tempQueryProps->next()) 
        {
            cout << tempQueryProps->getPropKey() << " " << tempQueryProps->queryPropValue() << endl;
        }
    }
}

void hpccInit::getAllMethods(const char* serviceName, const char* methodName, bool &flagSuccess) 
{
    auto *esdlServ = esdlDef->queryService(serviceName);
    if (!esdlServ) 
    {
        cerr << "Service not found: " << serviceName << endl;
        return;
    }

    try {
        auto *methodIter = esdlServ->getMethods();
        if (!methodIter) 
        {
            cerr << "No methods found for service: " << serviceName << endl;
            return;
        }

        for (methodIter->first(); methodIter->isValid(); methodIter->next()) 
        {
            auto &tempMethod = methodIter->query();
            if (strcmp(tempMethod.queryName(), methodName) == 0) 
            {
                traverseProps(tempMethod.queryRequestType());
                flagSuccess = true;
            }
        }
    } 
    catch (const std::exception &e) 
    {
        cerr << "Caught an exception: " << e.what() << endl;
    } 
    catch (...) 
    {
        cerr << "Caught an unknown exception!" << endl;
    }
}



void hpccInit::esdlDefInit(const char* serviceName, const char* methodName) 
{
    Owned<IFile> serviceDefFile;
    vector<string> fileList;
    getFileNames(fileList);

    for(const auto& file: fileList) 
    {
        cout << file << endl;
        const char* fileNameChar = file.c_str();

        serviceDefFile.setown(createIFile(fileNameChar));

        if(serviceDefFile->exists()) 
        {
            if(serviceDefFile->size() > 0) 
            {
                esdlDef->addDefinitionsFromFile(serviceDefFile->queryFilename());
            } else 
            {
                cerr << "File size zero" << endl;
            }
        }
        else 
        {
            throw(MakeStringException(0, "ESDL definition file source %s is not a file", "sourceFileName"));
        }
        

        bool flagSuccess = false;
        getAllMethods(serviceName, methodName, flagSuccess);
        if(flagSuccess) {
            break;
        }
    }
}

int main(int argc, const char* argv[])
{
    hpccInit myobj;


    // myobj.esdlDefInit("WsWorkunits", "WUAbort");

    // hpccShell myshell(argc,argv);
    return 0;
}