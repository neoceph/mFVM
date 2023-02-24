// Standard headers
#include <iostream>

// Third party headers
#include <Eigen/Sparse>

// User defined headers
#include <Properties.h>
#include <Discretization.h>
#include <InputProcessor.h>


FiniteVolumeMethod::FiniteVolumeMethod
    (
        InputProcessor *inputProcessorObject, 
        Properties *propertiesObject
    ):
    inputs(inputProcessorObject), 
    properties(propertiesObject)
{
    // TODO Auto-generated constructor stub
    this->assembleMatrix();

}

FiniteVolumeMethod::~FiniteVolumeMethod()
{
    // TODO Auto-generated constructor stub

}


void FiniteVolumeMethod::assembleMatrix()
{
    int dimension = static_cast<int>(inputs->nx);

    this->A.resize(dimension, dimension);
    this->b.resize(dimension);
 
    for (int i = 0; i < dimension; i++) 
    {
        A.insert(i, i) = 2.0;
        if (i > 0) {
            A.insert(i-1, i) = -1.0;
            A.insert(i, i-1) = -1.0;
        }
    }
    A.makeCompressed();

    b.setOnes();
    std::cout << "Sparse matrix A:\n" << A << std::endl;
    std::cout << "Sparse matrix b:\n" << b << std::endl;
}


// void FiniteVolumeMethod::assembleMatrix()
// {
//     // TODO Auto-generated constructor stub
    

//     Eigen::VectorXd b(inputs->nx);
    
//     for(int i = 0; i < inputs->nx; i++)
//     {
//         triplets.push_back(T(i,i,1));
//         b(i) = 1;

//     }
//     // A.resize(inputs->nx, inputs->nx);
//     SparseMat A(inputs->nx, inputs->nx);
//     A.setFromTriplets(triplets.begin(), triplets.end());

//     std::cout << "Sparse matrix A:\n" << A << std::endl;
//     std::cout << "Thermal Conductivity: " << properties->thermalConductivity << std::endl;

//     Eigen::SparseLU<SparseMat> solver;
//     solver.analyzePattern(A);
//     solver.factorize(A);


//     if (solver.info() != Eigen::Success) 
//     {
//         std::cerr << "Decomposition failed" << std::endl;
//         // return 1;
//     }

//     // Solve the linear system
//     Eigen::VectorXd x = solver.solve(b);

//     if (solver.info() != Eigen::Success) {
//         std::cerr << "Solving failed" << std::endl;
//         // return 1;
//     }

//     // Print the solution
//     std::cout << "Solution:\n" << x << std::endl;
// }