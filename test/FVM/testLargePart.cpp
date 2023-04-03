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
#include <Physics.h>
#include <Properties.h>

// #include "Example.hpp"
#include<gtest/gtest.h>

class LargePartTest : public ::testing::Test {
protected:
  
  InputProcessor* testInputProcessor;
  Properties* testProperties;
  ControlVolumeMesh* testMesh;
  FiniteVolumeMethod* testFVM;
  Solver* testSolver;

  void SetUp() override {
    // code to set up the test fixture   
    testInputProcessor = new InputProcessor();

    // setup the problem domains
    testInputProcessor->westBoundaryTemperature = 100.0;
    testInputProcessor->eastBoundaryTemperature = 200.0;
    testInputProcessor->heatFlux = 1000e3; // W/m^21
    testInputProcessor->nodeNumbers = {100, 100, 100};
    testInputProcessor->domainDimensions = {1.0, 1.0, 1.0};
    testInputProcessor->stateVariables = {
                {"Solid", 0}};                

    testProperties = new Properties(testInputProcessor);
    testMesh = new ControlVolumeMesh(testInputProcessor);
    testFVM = new FiniteVolumeMethod(testInputProcessor, testProperties, testMesh);
    testSolver = new Solver(testFVM);
    
  }

  void TearDown() override {
    // code to tear down the test fixture
    delete testInputProcessor;
    delete testProperties;
    delete testMesh;
    delete testFVM;
    delete testSolver;
  }
};

TEST_F(LargePartTest, vtkLargePart)
{
    char fileName[30] = "testLargePart.vts";
    char stateVariableName[30] = "Solid";
    double coordinate[3], radius;
    double minRadius = 0.5;

    for (int i=0; i<testMesh->totalNodes; i++)
    {
        testMesh->points->GetPoint(i, coordinate);
        radius = sqrt(pow(coordinate[0], 2) + pow(coordinate[1], 2));
        if (radius < minRadius)
        {
            // testMesh->nodeScalars->SetValue(i, 0.0);
            testSolver->nodeScalars.push_back(0.0);
            // std::cout<<testSolver->nodeScalars[i]<<std::endl;
        }
        else
        {
            testSolver->nodeScalars.push_back(1.0);
            // std::cout<<testSolver->nodeScalars[i]<<std::endl;
        }
    }


    for (int i=0; i<testMesh->totalCells; i++)
    {
        coordinate[0] = testMesh->cells[0].coordinate[0];
        coordinate[1] = testMesh->cells[i].coordinate[1];
        coordinate[2] = testMesh->cells[i].coordinate[2];

        radius = sqrt(pow(coordinate[0], 2) + pow(coordinate[1], 2));
        if (radius < minRadius)
        {
            // testMesh->nodeScalars->SetValue(i, 0.0);
            testSolver->cellScalars.push_back(0.0);
            // std::cout<<testSolver->cellScalars[i]<<std::endl;
        }
        else
        {
            testSolver->cellScalars.push_back(1.0);
            // std::cout<<testSolver->cellScalars[i]<<std::endl;
        }
    }

    testSolver->updateResults(stateVariableName, testSolver->nodeScalars, testSolver->cellScalars);
    testSolver->writeData(fileName);
}