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
    
    face.area = 1;
    std::cout<<face.area<<std::endl;
    // nodeNumber = inputs->nodeNumbers;
    cell.faces["east"].area = 1;
    // cell.faces["east"].coordinate[0] = 1.0;
    // cell.faces["east"].coordinate[1] = 2.0;
    // cell.faces["east"].coordinate[2] = 2.0;
    
    cells[1] = cell;
    std::cout<<cells[1].faces["east"].area<<std::endl;

    std::cout<<cell.faces["east"].area<<std::endl;

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

    xStep = domainDimensions[0] / (nodeNumbers[0]-1);
    yStep = domainDimensions[1] / (nodeNumbers[1]-1);
    zStep = domainDimensions[2] / (nodeNumbers[2]-1);


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
                points->GetPoint(pointID, coordinate); // getting the coordinate of the point
                // std::cout<<coordinate[0]<<" "<<coordinate[1]<<" "<<coordinate[2]<<std::endl;
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
    for (auto& cellVertex : cellVertexIds) // iterating through the cellVertexIds map
    {
        std::array<double, 3> center = {0.0, 0.0, 0.0}; // initializing the center of the cell to be zero
        for (auto& vertex : cellVertex.second) // iterating through the cellVertexIds map
        {
            double point[3]; // creating a double array to store the coordinates of the point
            this->controlVolumes->GetPoint(vertex, point); // getting the coordinates of the point
            center[0] += point[0]; // adding the x coordinate of the point to the x coordinate of the center
            center[1] += point[1]; // adding the y coordinate of the point to the y coordinate of the center
            center[2] += point[2]; // adding the z coordinate of the point to the z coordinate of the center

            // std::cout<<"Cell ID: "<<cell.first<<" Vertex ID: "<<vertex<<" Point: "<<point[0]<<" "<<point[1]<<" "<<point[2]<<std::endl;
        }
        center[0] /= cellVertex.second.size(); // dividing the x coordinate of the center by the number of points in the cell
        center[1] /= cellVertex.second.size(); // dividing the y coordinate of the center by the number of points in the cell
        center[2] /= cellVertex.second.size(); // dividing the z coordinate of the center by the number of points in the cell
        cellCenters[cellVertex.first] = center; // storing the center of the cell in the cellCenters map

        // cellSet[0] = cellVertex.first;

    }

    // for (auto it = cellCenters.begin(); it != cellCenters.end(); ++it) // iterating through the cellCenters map
    // {
    //     std::cout << "Cell ID: " << it->first << " Center: " << it->second[0] << " " << it->second[1] << " " << it->second[2] << std::endl;
    // }
}

void ControlVolumeMesh::generateFaceAreas()
{
    // clearing the pointsForSorting vector
        
    // iterate through cells and generate face areas
    for (auto& cell : cellVertexIds) // iterating through the cellVertexIds map
    {
        
        // Collecting the points of the cell for face area and face center calculation
        pointsForSorting.clear();
        // std::array<double, 3> center = {0.0, 0.0, 0.0}; // initializing the center of the cell to be zero
        for (auto& vertex : cell.second) // iterating through the cellVertexIds map
        {
            double pointCoordinate[3]; // creating a double array to store the coordinates of the point
            this->controlVolumes->GetPoint(vertex, pointCoordinate); // getting the coordinates of the point
            arma::vec vec(pointCoordinate, 3);
            pointsForSorting.push_back(vec);
            std::cout << "Cell ID: " << cell.first << " Vertex ID: " << vertex << " Point: " << pointCoordinate[0] << " " << pointCoordinate[1] << " " << pointCoordinate[2] << std::endl;

        }
        
        // transferring the pointsForSorting vector to an arma::mat object
        arma::mat sortedPoints(pointsForSorting.size(), 3);
        for (std::size_t i=0; i<pointsForSorting.size(); ++i)
        {
            sortedPoints.row(i) = pointsForSorting[i].t();
        }

        // // printing the sortedPoints before and after sorting
        // arma::cout << "Points Before Sorting:" << arma::endl;
        // arma::cout << sortedPoints << arma::endl;

        arma::cout << "Points After Sorting:" << arma::endl;
        sortedPoints = sortPoints(sortedPoints, 2);
        arma::cout << sortedPoints << arma::endl;

        arma::mat firstFour = sortedPoints.rows(0, 3);
        arma::mat lastFour = sortedPoints.rows(4, 7);
        
        // calculating the area of the faces
        arma::cout << "First four points: "<< std::endl << firstFour << std::endl;
        arma::cout << "Last four points: "<< std::endl << lastFour << std::endl;
        // calculating the area of the faces


        arma::cout << "Area of the bottom face: " << calculate_quadrilateral_area(firstFour) << std::endl;
        arma::cout << "Area of the top face: " << calculate_quadrilateral_area(lastFour) << std::endl;

    }   
}

/**
 * Sorts an `arma::mat` object by a specified axis.
 * 
 * @param points The input `arma::mat` object to be sorted.
 * @param axis The axis to sort the points by (0 for x-axis, 1 for y-axis, 2 for z-axis).
 * 
 * @return The sorted `arma::mat` object.
 */
arma::mat ControlVolumeMesh::sortPoints(const arma::mat& points, int axis)
{
    
    arma::mat sorted_points = points;
    sorted_points = sorted_points.rows(arma::sort_index(sorted_points.col(axis)));
    return sorted_points;
}

/**
 * @brief Calculates the area of a quadrilateral.
 * 
 * @param points in the form of an `arma::mat` object. 
 * @return double 
 */
double ControlVolumeMesh::calculate_quadrilateral_area(const arma::mat& points) 
{
       
    arma::mat l1 = points.rows(1, 1) - points.rows(0, 0);
    arma::mat l2 = points.rows(2, 2) - points.rows(0, 0);
    arma::mat crossProduct = arma::cross(l1, l2);

    double area = arma::norm(crossProduct);
    
    return std::abs(area);
}

