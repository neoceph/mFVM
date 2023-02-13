#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <typeinfo>

// external library headers
#include <Eigen/Dense>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkNew.h>

// self developed library headers
// #include "version.h"
#include "version.h"
#include "Mesh.h"
#include "Solver.h"

int main (int arg, char *argv[])
{

    VersionInfo version;
    size_t nx = 2, ny = 4, nz = 4;
    char fileName[] = "output.vts";
    
    // unsigned int dimension = 3;
    std::vector<unsigned int> nodeNumbers{static_cast<uint>(nx), static_cast<uint>(ny), static_cast<uint>(nz)};
    std::vector<double> domainDimension{2.0, 3.0, 2.0}; // defining the length of the entire domain

    std::cout << "Multiphase solver for Additive Manufacturing Problems!\n";


    if (arg != 2)
    {
        
        std::cout << "Missing parameter: input file name" << std::endl;
        std::cout << "Printing a test matrix" << std::endl;
        exit(1);
      return 0;
    }

    else
    {
        version.getVersionInfo(argv[1]);
    }

    ControlVolumeMesh mesh(nodeNumbers, domainDimension);
    Solver *amSolver = new Solver(&mesh);

    amSolver->updateResults();
    mesh.writeData(fileName);

}
