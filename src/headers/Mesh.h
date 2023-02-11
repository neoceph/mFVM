#ifndef MESH_H_
#define MESH_H_

// standard headers
#include <iterator>
#include <map>
#include <set>

// third party headers
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>


class ControlVolumeMesh
{
    public:
        ControlVolumeMesh(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize);
        ~ControlVolumeMesh();
        // double eastFaceArea = 1;

        vtkNew<vtkStructuredGrid> controlVolumes;
        vtkNew<vtkPoints> points;
        vtkNew<vtkDoubleArray> nodeScalars, nodeVectors, nodeTensors;
        vtkNew<vtkDoubleArray> cellScalars, cellVectors, cellTensors;

        void testFunction();
        void meshGeneration();
        void generatePoints(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize);
        void writeData(char* fileName);
};


#endif /* MESH_H_ */
