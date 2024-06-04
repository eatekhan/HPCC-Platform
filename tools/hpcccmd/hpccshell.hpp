#include "jargv.hpp"
#include "hpcccmd.hpp"
class hpccShell {
    public:
        hpccShell(int argc, const char* argv[]);
        ArgvIterator args;
        void parseCmdOptions(hpccInit myobj, int argc, const char* argv[]);
};