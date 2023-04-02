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

class MeshTest : public ::testing::Test {
protected:
  
  InputProcessor* testInputProcessor;
  Properties* testProperties;
  ControlVolumeMesh* testMesh;
  FiniteVolumeMethod* testFVM;

  void SetUp() override {
    // code to set up the test fixture
    testInputProcessor = new InputProcessor();

    // setup the problem domains
    testInputProcessor->westBoundaryTemperature = 100.0;
    testInputProcessor->eastBoundaryTemperature = 200.0;
    testInputProcessor->heatFlux = 1000e3; // W/m^21
    testInputProcessor->nodeNumbers = {2, 2, 2};
    testInputProcessor->domainDimensions = {1.0, 1.0, 1.0};
    testInputProcessor->myList = {
                {"Temp", 0}};

    testProperties = new Properties(testInputProcessor);
    testMesh = new ControlVolumeMesh(testInputProcessor);
    testFVM = new FiniteVolumeMethod(testInputProcessor, testProperties, testMesh);
    
  }

  void TearDown() override {
    // code to tear down the test fixture
    delete testInputProcessor;
    delete testProperties;
    delete testMesh;
  }
};

TEST_F(MeshTest, meshCoordinateTest)
{
    double estimatedCoordinate[3];
    double expectedCoordinate[3] = {0.0, 0.0, 0.0};

    expectedCoordinate[2] = 0.0;
    for (int k=0; k < 2; k++)
    {
        expectedCoordinate[2] += k;
        expectedCoordinate[1] = 0;
        for (int j=0; j<2; j++)
        {
            expectedCoordinate[1] += j;
            expectedCoordinate[0] = 0;
            for (int i=0; i<2; i++)
            {
                expectedCoordinate[0] += i;
                testMesh->points->GetPoint(i+2*j+2*2*k, estimatedCoordinate);
                for (int i = 0; i < 3; i++)
                {
                    ASSERT_NEAR(expectedCoordinate[i], estimatedCoordinate[i], 1e-6);
                }
            }
        }
    }
    

};


TEST_F(MeshTest, meshingProgressTest)
{
    const int total = 100; // total number of iterations
    int progress = 0;   
    
    // print initial empty progress bar
    std::cout << "[" << std::string(total, ' ') << "] 0%\r";
    std::cout.flush();

    for (int i = 0; i < total; ++i)
    {
        // update progress
        ++progress;

        // calculate percentage
        int percent = static_cast<int>((static_cast<double>(progress) / total) * 100);

        // update progress bar
        std::cout << "[" << std::string(progress, '#') << std::string(total - progress, ' ') << "] " << percent << "%\r";
        std::cout.flush();
    }
};
