#include "hpcccmd.hpp"
class hpccService : public hpccInit{
    public:

    hpccService(int argc, const char* argv[], const char* formArgs, const char* resType, const char* reqType, const char* target = "http://127.0.0.1:8010/",
 const char* username="default", const char* password="default");
};