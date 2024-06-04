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
    Owned<IEsdlDefinition> esdlDef;
    Owned<IEsdlDefinitionHelper> defHelper;

    void getFileNames(std::vector<std::string> &methodsList);
    void traverseProps(const char* reqRes);
    void getAllMethods(const char* serviceName, const char* methodName, bool &flagSuccess);

public:
    hpccInit();
    void esdlDefInit(const char* serviceName, const char* methodName);
};

#endif // HPCC_INIT_HPP
