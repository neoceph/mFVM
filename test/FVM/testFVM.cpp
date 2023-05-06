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
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <Math/Math.h>
#include <Math/GenVector/VectorUtil.h>

// User defined headers
#include <version.h>
#include <Mesh.h>
#include <Solver.h>
#include <Discretization.h>
#include <Physics.h>
#include <Properties.h>

// #include "Example.hpp"
#include<gtest/gtest.h>


// write a google test to test the Physics class and its methods
TEST(PhysicsTest, AddTest)
{
    Physics physics;
    int result = physics.add(3, 4);
    EXPECT_EQ(result, 7);
}

TEST(PhysicsMulTest, MultiplyTest)
{
    Physics physics;
    int result = physics.add(8, 4);
    EXPECT_EQ(result, 12);
}

TEST(ExampleTests, DemonstrateGTestMacros){
    EXPECT_TRUE(true);
}

TEST(GraphTests, PrintSineWave){
    int n = 1000;
    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        x[i] = i * 0.01;
        y[i] = ROOT::Math::sin(x[i]);
    }
    TGraph graph(n, x, y);
    graph.Draw("AL");
    graph.GetXaxis()->SetTitle("x");
    graph.GetYaxis()->SetTitle("y");
    TCanvas canvas("canvas", "canvas", 800, 600);
    canvas.cd();
    graph.Draw("AL");
    canvas.SaveAs("sine_wave.png");
    EXPECT_TRUE(true);
}