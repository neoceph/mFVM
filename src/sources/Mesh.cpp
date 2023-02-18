// Standard headers
#include <iterator>
#include <map>
#include <set>

// Third party headers
#include <armadillo>
#include <vtkCellIterator.h>
#include <vtkType.h>
#include <vtkXMLStructuredGridWriter.h>

// User defined headers
#include <Mesh.h>


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

    this->identifyCellVertex();
    this->generateCellCenters();
    this->generateFaceAreas();

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
                // points->GetPoint(pointID, coordinate); // getting the coordinate of the point
                x += xStep;
                pointID +=1;
                
            }
            y += yStep;
        }
        z += zStep;
    }
}


void ControlVolumeMesh::identifyCellVertex()
{
    vtkCellIterator* it = this->controlVolumes->NewCellIterator(); // creating an iterator to iterate through the list of cells.
    
    for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell()) //loop for iterating through the cells.
    {
        vtkPoints* points = it->GetPoints(); // getting the points of the cell

        vtkIdList* pointIds = it->GetPointIds();  // getting the point id of all the cell associated vertices (8 in this case)
        for (vtkIdType* id = pointIds->begin(); id != pointIds->end(); ++id)  //iterating through the pointIds list
        {
        vertexIds.insert(*id);  // inserting the ids of the points into the vertexIds set to be inserted into the cellVertexIds map
        }
        cellVertexIds[it->GetCellId()] = vertexIds; // storing all the point ids (ptIds) into the set for cell point IDs (created on line 83)
        vertexIds.clear(); // clearing the vertexIds set to be used for the next cell

    }
    it->Delete(); // deleting iterators

    for (auto& vertex : vertexIds)
    {
        std::cout<<"Cell ID: "<<it->GetCellId()<<" Vertex ID: "<<vertex<<std::endl;
    }
    
  
}

void ControlVolumeMesh::generateCellCenters()
{
    for (auto& cell : cellVertexIds) // iterating through the cellVertexIds map
    {
        std::array<double, 3> center = {0.0, 0.0, 0.0}; // initializing the center of the cell to be zero
        for (auto& vertex : cell.second) // iterating through the cellVertexIds map
        {
            double point[3]; // creating a double array to store the coordinates of the point
            this->controlVolumes->GetPoint(vertex, point); // getting the coordinates of the point
            center[0] += point[0]; // adding the x coordinate of the point to the x coordinate of the center
            center[1] += point[1]; // adding the y coordinate of the point to the y coordinate of the center
            center[2] += point[2]; // adding the z coordinate of the point to the z coordinate of the center

            // std::cout<<"Cell ID: "<<cell.first<<" Vertex ID: "<<vertex<<" Point: "<<point[0]<<" "<<point[1]<<" "<<point[2]<<std::endl;
        }
        center[0] /= cell.second.size(); // dividing the x coordinate of the center by the number of points in the cell
        center[1] /= cell.second.size(); // dividing the y coordinate of the center by the number of points in the cell
        center[2] /= cell.second.size(); // dividing the z coordinate of the center by the number of points in the cell
        cellCenters[cell.first] = center; // storing the center of the cell in the cellCenters map

    }

    // for (auto it = cellCenters.begin(); it != cellCenters.end(); ++it) // iterating through the cellCenters map
    // {
    //     std::cout << "Cell ID: " << it->first << " Center: " << it->second[0] << " " << it->second[1] << " " << it->second[2] << std::endl;
    // }
}

void ControlVolumeMesh::generateFaceAreas()
{
    // iterate through cells and generate face areas
    for (auto& cell : cellVertexIds) // iterating through the cellVertexIds map
    {
        // std::array<double, 3> center = {0.0, 0.0, 0.0}; // initializing the center of the cell to be zero
        for (auto& vertex : cell.second) // iterating through the cellVertexIds map
        {
            double point[3]; // creating a double array to store the coordinates of the point
            this->controlVolumes->GetPoint(vertex, point); // getting the coordinates of the point
            // center[0] += point[0]; // adding the x coordinate of the point to the x coordinate of the center
            // center[1] += point[1]; // adding the y coordinate of the point to the y coordinate of the center
            // center[2] += point[2]; // adding the z coordinate of the point to the z coordinate of the center
            std::cout << "Cell ID: " << cell.first << " Vertex ID: " << vertex << " Point: " << point[0] << " " << point[1] << " " << point[2] << std::endl;
        }

    }
}