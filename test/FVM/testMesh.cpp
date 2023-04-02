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

TEST_F(MeshTest, meshVertexTest)
{
    double estimatedCoordinate[3], expectedCoordinate[3] = {0.0, 0.0, 0.0};

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

TEST_F(MeshTest, meshFaceCenterTest)
{
    int j;
    double estimatedValue, expectedValue;
    double expectedCellCenterCoordinate[3] = {0.0, 0.5, 0.5};
    std::map<std::string, double> expectedFaceArea{{"East", 1.0}, {"West", 1.0}, {"North", 1.0}, {"South", 1.0}, {"Top", 1.0}, {"Bottom", 1.0}};
    std::map<std::string, std::array<double, 3>> expectedFaceCoordinate{
        {"East", {1.0, 0.5, 0.5}}, 
        {"West", {0.0, 0.5, 0.5}}, 
        {"North", {0.5, 1.0, 0.5}}, 
        {"South", {0.5, 0.0, 0.5}}, 
        {"Top", {0.5, 0.5, 1.0}}, 
        {"Bottom", {0.5, 0.5, 0.0}},
        };

    for (const auto& pair: expectedFaceArea)
    {
        estimatedValue = testMesh->cells[0].faces[pair.first].area;
        expectedValue = pair.second;
        ASSERT_NEAR(expectedValue, estimatedValue, 1e-6);
        
        for (const auto& coordinatePair: expectedFaceCoordinate)
        {
             for (int i = 0; i < 3; i++)   
             {
                estimatedValue = testMesh->cells[0].faces[coordinatePair.first].coordinate[i];
                expectedValue = coordinatePair.second[i];
                ASSERT_NEAR(expectedValue, estimatedValue, 1e-6);

             }
        }
    }
    

};

TEST_F(MeshTest, meshCellCenterTest)
{
    double expectedCellCenterCoordinate[3] = {0.5, 0.5, 0.5};

    for (int i = 0; i < 3; i++)
    {
        ASSERT_NEAR(expectedCellCenterCoordinate[i], testMesh->cells[0].coordinate[i], 1e-6);
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
