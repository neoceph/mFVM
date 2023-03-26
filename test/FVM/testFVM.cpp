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
