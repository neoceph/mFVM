#ifndef SOLVER_H_
#define SOLVER_H_

// third party headers
#include <Mesh.h>

class ControlVolumeMesh;

class Solver
{
    public:
        // Constructor
        Solver(ControlVolumeMesh *meshObject);
        // Destructor
        ~Solver();

        //Input
        ControlVolumeMesh *mesh;

        // methods
        void updateResults();
};


#endif /* SOLVER_H_ */
