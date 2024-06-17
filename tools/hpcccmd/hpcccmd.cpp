#include <cstring>
#include <iostream>
#include "esdl_def.hpp"
#include "jlog.hpp"
#include "jprop.hpp"
#include "esdl_def.hpp"
#include "esdl_def_helper.hpp"
#include "jscm.hpp"
#include "jstring.hpp"
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include "hpcccmd.hpp"
#include "hpccshell.hpp"
#include "httpclient.hpp"
#include "hpccservice.hpp"

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
    queryLogMsgManager()->removeMonitor(queryStderrLogMsgHandler());   
    esdlDef.setown(createEsdlDefinition(nullptr, createConcreteEsdlDefReporter));
    defHelper.setown(createEsdlDefinitionHelper());
    IEsdlDefReporter* reporter = esdlDef->queryReporter();
    using TraceFlags = IEsdlDefReporter::Flags;
    TraceFlags traceFlags = IEsdlDefReporter::ReportDisaster;
    reporter->setFlags(traceFlags, true);

    
    vector<string> fileList;
    getFileNames(fileList);

    for(const auto& file: fileList) 
    {
        //cout << file << endl;
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
    }
    loadAllServices();

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

void hpccInit::printHelper(const char* props)
{
    IEsdlDefStruct* structComplexType = esdlDef->queryStruct(props);
    Owned<IEsdlDefObjectIterator> structChildrenIterator = structComplexType->getChildren();

    for(structChildrenIterator->first();structChildrenIterator->isValid();structChildrenIterator->next())
    {
       IEsdlDefObject &tempQuery = structChildrenIterator->query();
       Owned<IPropertyIterator> tempQueryProps = tempQuery.getProps();
       for(tempQueryProps->first();tempQueryProps->isValid();tempQueryProps->next()) 
       {
           const char* propKey = tempQueryProps->getPropKey();
           cout << "\t\t" << propKey << " " << tempQueryProps->queryPropValue() << " ";
       }
       cout << endl; 
    }
}

void hpccInit::traverseProps(const char* reqRes) 
{
    IEsdlDefStruct* myStruct = esdlDef->queryStruct(reqRes);
    cout << myStruct->queryName() << endl;

    Owned<IEsdlDefObjectIterator> structChildren = myStruct->getChildren();
   

    for(structChildren->first();structChildren->isValid();structChildren->next()) 
    {
        IEsdlDefObject &tempQuery = structChildren->query();
        Owned<IPropertyIterator> tempQueryProps = tempQuery.getProps();
        for(tempQueryProps->first();tempQueryProps->isValid();tempQueryProps->next()) 
        {
            const char* propKey = tempQueryProps->getPropKey();
            cout << "\t" << propKey << "=" << tempQueryProps->queryPropValue() << " ";
            if(strcmp(propKey, "complex_type")==0)
            {
                cout << endl;
                printHelper(tempQueryProps->queryPropValue());
            }
        }
        cout << endl;
    }
}

bool hpccInit::checkValidService(const char* serviceName)
{
    for(auto &service : allServicesList)
    {
        if(strcmp(service, serviceName) == 0)
        {
            cout << "valid service" << endl;
            return true;
        }
    }
    cout << "invalid service" << endl;
    return false;
}

bool hpccInit::checkValidMethod(const char* methodName, const char* serviceName)
{
    IEsdlDefService *esdlServ = esdlDef->queryService(serviceName);

    if (!esdlServ) 
    {
        cerr << "No Service: printAllMethods" << endl;
        return false;
    }

    // IEsdlDefMethodIterator *methodIter = esdlServ->getMethods();
    Owned<IEsdlDefMethodIterator> methodIter = esdlServ->getMethods();
    if (!methodIter) 
    {
        cerr << "No methods found for service: " << serviceName << endl;
        return false;
    }

    for (methodIter->first(); methodIter->isValid(); methodIter->next()) 
    {
        auto &tempMethod = methodIter->query();
        if (strcmp(tempMethod.queryName(), methodName) == 0) 
        {
            cout << "Valid Method" << endl;
            return true;
        }
    }
    cout << "Invalid Method" << endl;
    return false;
}

void hpccInit::loadAllServices()
{
    Owned<IEsdlDefServiceIterator> serviceIter = esdlDef->getServiceIterator();
    for(serviceIter->first();serviceIter->isValid();serviceIter->next())
    {
        IEsdlDefService &currentService = serviceIter->query();
        const char* serviceName = currentService.queryName();
        //cout << serviceName <<endl;
        allServicesList.push_back(serviceName);
    }
}


void hpccInit::loadAllMethods(const char* serviceName)
{
    IEsdlDefService *esdlServ = esdlDef->queryService(serviceName);
    // Owned<IEsdlDefService> esdlServ = esdlDef->queryService(serviceName);
    if (!esdlServ) 
    {
        cerr << "No Service: loadAllMethods" << endl;
        return;
    }

    // IEsdlDefMethodIterator *methodIter = esdlServ->getMethods();
    Owned<IEsdlDefMethodIterator> methodIter = esdlServ->getMethods();
    if (!methodIter) 
    {
        cerr << "No methods found :loadAllMethods " << endl;
        return;
    }
    for (methodIter->first(); methodIter->isValid(); methodIter->next()) 
    {
        auto &tempMethod = methodIter->query();
        allMethodsList.push_back(tempMethod.queryMethodName());
    }
}

void hpccInit::printAllServices()
{
    for(auto &serv:allServicesList)
    {
        cout << serv << endl;
    }
}

void hpccInit::printAllMethods(const char* serviceName)
{
    auto *esdlServ = esdlDef->queryService(serviceName);
    if (!esdlServ) 
    {
        cerr << "No Service: printAllMethods" << endl;
    }

    auto *methodIter = esdlServ->getMethods();
    if (!methodIter) 
    {
        cerr << "No methods found for service (printAllMethods)" << serviceName << endl;
    }

    for (methodIter->first(); methodIter->isValid(); methodIter->next()) 
    {
        auto &tempMethod = methodIter->query();
        cout << tempMethod.queryMethodName() << endl;
    }
}


void hpccInit::esdlDefInit(const char* serviceName, const char* methodName) 
{
    
    loadAllServices();
    loadAllMethods(serviceName);
    if(!checkValidService(serviceName))
    {
        return;
    }
    if(!checkValidMethod(methodName, serviceName))
    {
        return;
    }

    IEsdlDefService *esdlServ = esdlDef->queryService(serviceName);

    // IEsdlDefMethodIterator *methodIter = esdlServ->getMethods();
    Owned<IEsdlDefMethodIterator> methodIter = esdlServ->getMethods();
    for (methodIter->first(); methodIter->isValid(); methodIter->next()) 
    {
        auto &tempMethod = methodIter->query();
        if (strcmp(tempMethod.queryName(), methodName) == 0) 
        {
            traverseProps(tempMethod.queryRequestType());
            traverseProps(tempMethod.queryResponseType());
        }
    }
}


int main(int argc, const char* argv[])
{
    
    InitModuleObjects();

  

    hpccShell myshell(argc,argv);

    
    
    
    return 0;
}

