#include<gtest/gtest.h>
#include <petsc.h>

TEST(PETScHelloWorldTest, PrintHelloWorld) {
  PetscInitialize(NULL, NULL, NULL, NULL); // Initialize PETSc

  testing::internal::CaptureStdout(); // Redirect stdout to capture output

  PetscPrintf(PETSC_COMM_WORLD, "Hello, World!\n");

  std::string output = testing::internal::GetCapturedStdout(); // Get captured output
  EXPECT_EQ(output, "Hello, World!\n");

  PetscFinalize(); // Finalize PETSc
}