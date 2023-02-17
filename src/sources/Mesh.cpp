#include <iterator>
#include <map>
#include <set>

// Third party headers
#include <vtkCellIterator.h>
#include <vtkXMLStructuredGridWriter.h>

// User defined headers
#include "Mesh.h"


// ControlVolumeMesh::ControlVolumeMesh(
//     std::vector<unsigned int> nodeNumbers, 
//     std::vector<double> domainDimensions, 
//     std::set<std::pair<std::string, int>> stateVariables
//     )
ControlVolumeMesh::ControlVolumeMesh(InputProcessor *inputProcessorObject):inputs(inputProcessorObject)
{
    // nodeNumber = inputs->nodeNumbers;
    totalNodes = inputs->nodeNumbers[0] * inputs->nodeNumbers[1] * inputs->nodeNumbers[2];
    totalCells = (inputs->nodeNumbers[0] - 1) * (inputs->nodeNumbers[1] - 1) * (inputs->nodeNumbers[2] - 1);
    
    this->stateVariables = inputs->stateVariables;

    this->controlVolumes->SetDimensions(inputs->nodeNumbers[0], inputs->nodeNumbers[1], inputs->nodeNumbers[2]);
    this->generatePoints(inputs->nodeNumbers, inputs->domainDimensions);
    this->controlVolumes->SetPoints(this->points);

}

ControlVolumeMesh::~ControlVolumeMesh()
{
    // destructor definition
}

void ControlVolumeMesh::meshGeneration()

{
    int nx, ny, nz;

}

void ControlVolumeMesh::generatePoints(std::vector<unsigned int> nodeNumbers, std::vector<double> domainDimensions)
{
    double xStep, yStep, zStep;

    xStep = domainDimensions[0] / nodeNumbers[0];
    yStep = domainDimensions[1] / nodeNumbers[1];
    zStep = domainDimensions[2] / nodeNumbers[2];


    auto x = 0.0;
    auto y = 0.0;
    auto z = 0.0;
    double coordinate[3];
    int pointID=0;
    for (unsigned int k = 0; k < nodeNumbers[2]; k++)
    {
        y = 0.0;
        for (unsigned int j = 0; j < nodeNumbers[1]; j++)
        {
            x = 0.0;
            for (unsigned int i = 0; i < nodeNumbers[0]; i++)
            {
                points->InsertNextPoint(x, y, z);
                points->GetPoint(pointID, coordinate);
                x += xStep;
                pointID +=1;
                
            }
            y += yStep;
        }
        z += zStep;
    }
}


void ControlVolumeMesh::getCellPoints()
{
    std::map<vtkIdType, std::set<vtkIdType>> cellPointIds; // creating a set of cell point IDs.
    vtkCellIterator* it = this->controlVolumes->NewCellIterator(); // creating an iterator to iterate through the list of cells.
    std::set<vtkIdType> ptIds;  // creating a set of vtkIdType with variable name ptIds
    
    for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell()) //loop for iterating through the cells.
    {
        vtkIdList* pointIds = it->GetPointIds();  // getting the point id of all the cell associated vertices (8 in this case)
        for (vtkIdType* id = pointIds->begin(); id != pointIds->end(); ++id)  //iterating through the pointIds list
        {
        ptIds.insert(*id);  // inserting the ids of the points into the ptIds.
        }
        cellPointIds[it->GetCellId()] = ptIds; // storing all the point ids (ptIds) into the set for cell point IDs (created on line 76)
    }
    it->Delete(); // deleting iterators
  
}