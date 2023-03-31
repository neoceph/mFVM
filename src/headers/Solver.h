#ifndef SOLVER_H_
#define SOLVER_H_

// Standard headers
#include <map>

// Third party headers
#include <vtkDoubleArray.h>
#include <vtkNew.h>

// User defined headers
#include <Mesh.h>
#include <Discretization.h>

class ControlVolumeMesh;

class Solver
{
    public:
        // Constructor
        Solver(FiniteVolumeMethod *FVMObject);
        // Destructor
        ~Solver();

        //Input
        FiniteVolumeMethod *FVM;

        //variables
        std::map<std::string, vtkNew<vtkDoubleArray>> nodeScalarTest, nodalVariables, cellVariables;
        vtkNew<vtkDoubleArray> nodeScalars, nodeVectors, nodeTensors;
        vtkNew<vtkDoubleArray> cellScalars, cellVectors, cellTensors;
        double radius_x, radius_y, radius_z;

        // methods
        void updateResults();
        void writeData(char* fileName);
        void solve();
        void buildPart();
};


#endif /* SOLVER_H_ */
