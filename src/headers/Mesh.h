#ifndef MESH_H_
#define MESH_H_

// standard headers
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Mesh 
{
    public:
        // Constructor
        Mesh(string fileName);
         
        // Destructor
        virtual ~Mesh();
    
        // Local functions/subroutines
        void getDomainInfo();

  
};

#endif /* MESH_H_ */
