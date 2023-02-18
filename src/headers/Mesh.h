#ifndef MESH_H_
#define MESH_H_

// standard headers
#include <iterator>
#include <map>
#include <set>

// third party headers
#include <vector>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>

// User defined headers
#include <InputProcessor.h>

class ControlVolumeMesh
{
    public:
        ControlVolumeMesh(InputProcessor *inputProcessorObject);
        ~ControlVolumeMesh();

        // Input
        InputProcessor *inputs;
        
        // double eastFaceArea = 1;

        int totalNodes, totalCells;

        std::set<std::pair<std::string, int>> stateVariables;

        std::vector<double> x_grid_;

        vtkNew<vtkStructuredGrid> controlVolumes;
        vtkNew<vtkPoints> points;
        vtkNew<vtkDoubleArray> nodeScalars, nodeVectors, nodeTensors;
        vtkNew<vtkDoubleArray> cellScalars, cellVectors, cellTensors;

        std::set<vtkIdType> vertexIds;  // creating a set of vtkIdType with variable name ptIds
        std::map<vtkIdType, std::set<vtkIdType>> cellVertexIds; // creating a set of cell vertex IDs and storing them by cell IDs.
        std::map<vtkIdType, std::array<double, 3>> cellCenters; // creating a set of cell center and storing them by cell IDs.


        void meshGeneration();
        void generatePoints(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize);
        void identifyCellVertex();
        void generateCellCenters();
        void generateFaceAreas();
};


#endif /* MESH_H_ */
