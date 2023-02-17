#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <typeinfo>
#include <chrono>

// external library headers
#include <Eigen/Dense>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkNew.h>
#include <vtkDoubleArray.h>

// self developed library headers
// #include "version.h"
#include <version.h>
#include <Mesh.h>
#include <Solver.h>

int main (int arg, char *argv[])
{

    auto start = std::chrono::high_resolution_clock::now();

    VersionInfo version;
    std::set<std::pair<std::string, int>> stateVariables;
    // size_t nx = 2, ny = 4, nz = 4;
    size_t nx = 450, ny = 250, nz = 200;
    char fileName[] = "output.vts";
    
    stateVariables.insert(std::make_pair("Temp", 0));
    stateVariables.insert(std::make_pair("Vel", 1));
    stateVariables.insert(std::make_pair("Str", 2));

    // creating a list and set then assign the list to the set
    std::list<std::string> stateVariablesList{"Temp", "Vel", "Str", "Temp"};
    std::set<std::string> stateVariablesSet(stateVariablesList.begin(), stateVariablesList.end());

    std::cout<<"The number of state variables is: "<<stateVariablesSet.size()<<std::endl;
    for (const auto &stateVariable : stateVariablesSet)
    {
        std::cout<<stateVariable<<std::endl;
    }
    
    std::cout<<"Printing a new Line"<<std::endl;
    
    for (const auto &stateVariable : stateVariablesList)
    {
        std::cout<<stateVariable<<std::endl;
    }

    // unsigned int dimension = 3;
    std::vector<unsigned int> nodeNumbers{static_cast<uint>(nx), static_cast<uint>(ny), static_cast<uint>(nz)};
    // std::vector<double> domainDimension{2.0, 3.0, 2.0}; // defining the length of the entire domain
    std::vector<double> domainDimension{4.5, 2.5, 2.0}; // defining the length of the entire domain

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

    ControlVolumeMesh mesh(nodeNumbers, domainDimension, stateVariables);
    Solver *amSolver = new Solver(&mesh);

    amSolver->updateResults();
    amSolver->writeData(fileName);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"Time Elapsed: "<<elapsed.count()<<" seconds"<<std::endl;

}
