#include "hpcccmd.hpp"
class hpccService : public hpccInit{
    public:

    hpccService(const char* serviceName, const char* methodName, const char* formArgs, const char* resType, const char* reqType, const char* target,
 const char* username="default", const char* password="default");
};