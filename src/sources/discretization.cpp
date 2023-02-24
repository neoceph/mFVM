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
    // TODO Auto-generated constructor stub
    
    for(int i = 0; i < inputs->nx; i++)
    {
        triplets.push_back(T(i,i,1));
    }
    A.resize(inputs->nx, inputs->nx);
    A.setFromTriplets(triplets.begin(), triplets.end());

    std::cout << "Sparse matrix A:\n" << A << std::endl;
    std::cout << "Thermal Conductivity: " << properties->thermalConductivity << std::endl;
}