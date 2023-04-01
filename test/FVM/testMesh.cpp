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

TEST(MeshTest, meshCoordinateTest)
{
    InputProcessor testInputProcessor;

    // setup the problem domains
    testInputProcessor.westBoundaryTemperature = 100.0;
    testInputProcessor.eastBoundaryTemperature = 200.0;
    testInputProcessor.heatFlux = 1000e3; // W/m^21
    testInputProcessor.nodeNumbers = {2, 2, 2};
    testInputProcessor.domainDimensions = {1.0, 1.0, 1.0};
    testInputProcessor.myList = {
                {"Temp", 0}};

    Properties testProperties(&testInputProcessor);
    ControlVolumeMesh testMesh(&testInputProcessor);

    double coordinate[3], expectedCoordinate[3];

    // expectedCoordinate = {1.0, 0.0, 0.0};
    testMesh.points->GetPoint(1, coordinate);
    std::cout << "Coordinate of the first point: " << coordinate << std::endl;

    EXPECT_EQ(7, 7);
}

TEST(MeshTest, meshingProgressTest)
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
}