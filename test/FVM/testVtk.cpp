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

TEST(VTKTest, solveLarge)
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

    testSolver.buildPart();
    testSolver.updateResults();
    testSolver.writeData(testInputProcessor.fileName);
}