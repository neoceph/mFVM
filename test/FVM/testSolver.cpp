// Standard headers

// Third party headers
#include<gtest/gtest.h>
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


// write a google test to test the Physics class and its methods
// TEST(SolverTest, solveTest)
// {
//     Solver solver;
//     // int result = physics.add(3, 4);
//     EXPECT_EQ(7, 7);
// }

// write a google test to test the Solver class and its method solve
TEST(SolverTest, solveTest)
{
    InputProcessor testInputProcessor;

    // setup the problem domains
    testInputProcessor.nx = 6;
    testInputProcessor.ny = 2;
    testInputProcessor.nz = 2;
    testInputProcessor.westBoundaryTemperature = 100.0;
    testInputProcessor.eastBoundaryTemperature = 200.0;
    testInputProcessor.heatFlux = 1000e3; // W/m^21
    testInputProcessor.domainDimensions = {2e-2, 1.0, 1.0};
    testInputProcessor.myList = {
                {"Temp", 0}};

    Properties testProperties(&testInputProcessor);
    ControlVolumeMesh testMesh(&testInputProcessor);
    FiniteVolumeMethod testFVM(&testInputProcessor, &testProperties, &testMesh);

    Solver testSolver(&testFVM);
    testSolver.solve();


    EXPECT_EQ(7, 7);
}