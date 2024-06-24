#ifndef HPCC_INIT_HPP
#define HPCC_INIT_HPP

#include <vector>
#include <string>
#include <cstring>
#include "esdl_def.hpp"
#include "esdl_def.hpp"
#include "esdl_def_helper.hpp"
// #include "hpccshell.hpp"
#include <string>
#include <vector>


class hpccInit {
private:
    // Owned<IEsdlDefinition> esdlDef;
    Owned<IEsdlDefinitionHelper> defHelper;
    std::vector<const char*> allServicesList;
    std::vector<const char*> allMethodsList;
    Owned<IFile> serviceDefFile;

    void getFileNames(std::vector<std::string> &methodsList);
    void traverseProps(const char* reqRes, int indent);
    void getAllMethods(const char* serviceName, const char* methodName, bool &flagSuccess);
    void loadAllServices();
    void loadAllMethods(const char* serviceName);
    
    void printHelper(const char* props);

    
    
protected:
    Owned<IEsdlDefinition> esdlDef;
    

// hpcc serv method --Wuids=test,test2 --blocktillfinish=0
// hpcc serv method --debugvalue (name:abc key:xyz)

public:

    hpccInit();
    void esdlDefInit(const char* serviceName, const char* methodName);
    void printAllServices();
    void printAllMethods(const char* serviceName);
    bool checkValidService(const char* serviceName);
    bool checkValidMethod(const char* methodName, const char* serviceName);
};

#endif // HPCC_INIT_HPP
