#ifndef DomainManager_h
#define DomainManager_h

// standard headers

// user-defined headers
#include <Mesh.h>

// define some classes to be used
class Mesh;

class DomainManager
{
    public:
        // Constructor
        DomainManager(Mesh *meshObj);
        
        // Destructor
        virtual ~DomainManager() {}; 
        
        // Input
        Mesh *meshObj_;

        // Local variables
          // input variables 
        int nzx_, nzy_, nzz_;
        void getHeatSourceParameters();
};

#endif

