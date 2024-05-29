#include <iostream>
#include "esdl_def.hpp"
#include "jprop.hpp"
#include "esdl_def.hpp"
#include "esdl_def_helper.hpp"
#include "jstring.hpp"
#include "hpccshell.cpp"
#include <vector>
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

void getAllMethods(Owned<IEsdlDefinition> &esdlDef)
{
    auto *esdlServ = esdlDef->queryService("WsTopology");
    auto *methodIter = esdlServ->getMethods();
    methodIter->first();
    for(;methodIter->isValid();methodIter->next())
    {
        auto &tempMethod =  methodIter->query();
        //cout << tempMethod.queryMethodName() << " " << tempMethod.queryRequestType() << endl;
        traverseProps(esdlDef, tempMethod.queryRequestType());
    }

}
void esdlDefInit()
{
    Owned<IFile> serviceDefFile;
    Owned<IEsdlDefinition> esdlDef;
    Owned<IEsdlDefinitionHelper> defHelper;


    esdlDef.set(createEsdlDefinition(nullptr, createConcreteEsdlDefReporter));
    defHelper.setown(createEsdlDefinitionHelper());
    IEsdlDefReporter* reporter = esdlDef->queryReporter();
    IEsdlDefReporter::Flags traceFlags = IEsdlDefReporter::ReportErrorClass;


    serviceDefFile.setown( createIFile("/home/khan/HPCC-Platform/tools/hpcccmd/ws_topology.xml") );
    if(serviceDefFile->exists())
    {
        if( serviceDefFile->size() > 0 )
        {
            esdlDef->addDefinitionsFromFile( serviceDefFile->queryFilename() );
            IEsdlDefObject *myobj = esdlDef->queryObj("ws_topology");
        }
    }
    else
        {
            throw( MakeStringException(0, "ESDL definition file source %s is not a file", "sourceFileName") );
        }
    //traverseMethods(esdlDef);
    getAllMethods(esdlDef);
   

}




int main(int argc, const char* argv[])
{
    InitModuleObjects();
    
    esdlDefInit();



















    // auto arg = ArgvIterator(argc, argv);

    // StringAttr someVal = "X";

    // cout << arg.isValid();

    // if(arg.matchFlag(someVal,"X"))
    // {
    //     cout << "match" << endl;
    // }



    
    return 0;
}