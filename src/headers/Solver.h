#ifndef SOLVER_H_
#define SOLVER_H_

// Standard headers
#include <map>

// Third party headers
#include <vtkDoubleArray.h>
#include <vtkNew.h>

// User defined headers
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

        //variables
        std::map<std::string, vtkNew<vtkDoubleArray>> nodeScalarTest, nodalVariables, cellVariables;
        vtkNew<vtkDoubleArray> nodeScalars, nodeVectors, nodeTensors;
        vtkNew<vtkDoubleArray> cellScalars, cellVectors, cellTensors;

        // methods
        void updateResults();
        void writeData(char* fileName);
};


#endif /* SOLVER_H_ */