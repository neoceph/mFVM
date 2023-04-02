// Standard headers
#include <iostream>

// Third party headers
#include <Eigen/Sparse>

// User defined headers
#include <Discretization.h>
#include <InputProcessor.h>
#include <Mesh.h>
#include <Properties.h>


FiniteVolumeMethod::FiniteVolumeMethod
    (
        InputProcessor *inputProcessorObject, 
        Properties *propertiesObject,
        ControlVolumeMesh *meshObject
    ):
    inputs(inputProcessorObject), 
    properties(propertiesObject),
    mesh(meshObject)
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
    int dimension = static_cast<int>(inputs->nodeNumbers[0]-1);

    this->A.resize(dimension, dimension);
    this->b.resize(dimension);
    this->initialTemperatures.resize(dimension);
 
    b.setZero();

    initialTemperatures(0) = inputs->westBoundaryTemperature;
    initialTemperatures(dimension-1) = inputs->eastBoundaryTemperature;


    for (int i = 0; i < dimension; i++) 
    {

        dx = mesh->cells[i].faces["East"].coordinate[0] - mesh->cells[i].faces["West"].coordinate[0];
        dy = mesh->cells[i].faces["North"].coordinate[1] - mesh->cells[i].faces["South"].coordinate[1];
        dz = mesh->cells[i].faces["Top"].coordinate[2] - mesh->cells[i].faces["Bottom"].coordinate[2];

        b(i) = 2.0 * ((mesh->cells[i].faces["West"].area * properties->thermalConductivity) / (dx)) * initialTemperatures(i) + (inputs->heatFlux * mesh->cells[i].faces["West"].area) * dx;
        
        westFlux = (mesh->cells[i].faces["West"].area * properties->thermalConductivity) / (dx);
        eastFlux = (mesh->cells[i].faces["East"].area * properties->thermalConductivity) / (dx);
        
        if (i > 0) {
            A.insert(i-1, i) = -eastFlux;
            A.insert(i, i-1) = -westFlux;
        }

        if (i == 0) {
            pointSource = -2.0 * properties->thermalConductivity * mesh->cells[i].faces["West"].area / (dx);
            westFlux = 0.0;
        }
        else if (i == dimension-1)
        {
            pointSource = -2.0 * properties->thermalConductivity * mesh->cells[i].faces["East"].area / (dx);
            eastFlux = 0.0;
        }
        else
        {
            pointSource = 0.0;
        }

        pointFlux = westFlux + eastFlux - pointSource;
        A.insert(i, i) = pointFlux;
    }
    A.makeCompressed();
}
