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
    testInputProcessor->nodeNumbers = {5, 5, 5};
    testInputProcessor->domainDimensions = {1.0, 1.0, 1.0};
    testInputProcessor->myList = {
                {"Temp", 0}};
    testInputProcessor->stateVariables = {
                {"Temp", 0}};                

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
    testSolver->updateAllResults();
    testSolver->writeData(fileName);
}