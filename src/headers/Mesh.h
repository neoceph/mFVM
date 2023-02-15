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


class ControlVolumeMesh
{
    public:
        ControlVolumeMesh(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize, std::set<std::pair<std::string, int>> stateVariables);
        ~ControlVolumeMesh();
        // double eastFaceArea = 1;

        int totalNodes, totalCells;

        std::set<std::pair<std::string, int>> stateVariables;

        std::vector<double> x_grid_;

        vtkNew<vtkStructuredGrid> controlVolumes;
        vtkNew<vtkPoints> points;
        vtkNew<vtkDoubleArray> nodeScalars, nodeVectors, nodeTensors;
        vtkNew<vtkDoubleArray> cellScalars, cellVectors, cellTensors;

        void meshGeneration();
        void generatePoints(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize);
        void getCellPoints();
};


#endif /* MESH_H_ */
