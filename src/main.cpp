// Standard headers
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <typeinfo>
#include <string>
#include <vector>

// Third party headers
#include <Eigen/Dense>
#include <vtkDoubleArray.h>
#include <vtkNew.h>
#include <vtkXMLStructuredGridWriter.h>


// User defined headers
#include <version.h>
#include <Mesh.h>
#include <Solver.h>
#include <Discretization.h>
#include <Properties.h>

int main (int arg, char *argv[])
{

    auto start = std::chrono::high_resolution_clock::now();

    VersionInfo version;
    std::set<std::pair<std::string, int>> stateVariables;

    
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

    // beginning of the analysis

    // initializing the objects
    InputProcessor inputProcessor;
    
    Properties Properties(&inputProcessor);
    ControlVolumeMesh mesh(&inputProcessor);
    FiniteVolumeMethod FVM(&inputProcessor, &Properties);
    
    Solver amSolver(&mesh, &FVM);

    amSolver.solve();
    amSolver.updateResults();
    amSolver.writeData(inputProcessor.fileName);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"Time Elapsed: "<<elapsed.count()<<" seconds"<<std::endl;

}
