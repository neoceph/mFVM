#ifndef MESH_H_
#define MESH_H_

// standard headers
#include <iterator>
#include <map>
#include <set>

// third party headers
#include <armadillo>
#include <vector>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>

// User defined headers
#include <InputProcessor.h>


// Struct for face properties
struct Face
{
    double area;
    double coordinate[3];
};

// Struct for cell properties
struct Cell
{
    std::map<std::string, Face> faces;
};

// Class for control volume mesh
class ControlVolumeMesh
{
    public:
        ControlVolumeMesh(InputProcessor *inputProcessorObject);
        ~ControlVolumeMesh();

        // Input
        InputProcessor *inputs;
        Face face;
        Cell cell;
        

        // double eastFaceArea = 1;

        int totalNodes, totalCells;

        std::set<std::pair<std::string, int>> stateVariables;
        std::map<vtkIdType, Cell> cells;
        std::vector<double> x_grid_;

        vtkNew<vtkStructuredGrid> controlVolumes;
        vtkNew<vtkPoints> points;
        std::vector<arma::vec> pointsForSorting;
        vtkNew<vtkDoubleArray> nodeScalars, nodeVectors, nodeTensors;
        vtkNew<vtkDoubleArray> cellScalars, cellVectors, cellTensors;
        std::vector<std::pair<std::string, std::string>> faceNames = {{"West", "East"}, {"South", "North"}, {"Bottom", "Top"}};

        std::set<std::string, double> faceAreas;
        std::set<vtkIdType, double> faceCenters;
        std::set<vtkIdType> vertexIds;  // creating a set of vtkIdType with variable name ptIds
        std::map<vtkIdType, std::set<vtkIdType>> cellVertexIds; // creating a set of cell vertex IDs and storing them by cell IDs.
        std::map<vtkIdType, std::array<double, 3>> cellCenters; // creating a set of cell center and storing them by cell IDs.


        void meshGeneration();
        void generatePoints(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize);
        void identifyCellVertex();
        void generateCellCenters();
        void generateFaceAreas();
        arma::mat sortPoints(const arma::mat& points, int axis);
        double calculate_quadrilateral_area(const arma::mat& points);
};


#endif /* MESH_H_ */
