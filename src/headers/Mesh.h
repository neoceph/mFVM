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


class ControlVolumeMesh: public vtkNew<vtkStructuredGrid>
// class ControlVolumeMesh: public vtkStructuredGrid
{
    public:
        // ControlVolumeMesh(void){}
        ControlVolumeMesh(size_t nx, size_t ny, size_t nz);
        ~ControlVolumeMesh();
        // double eastFaceArea = 1;
        void testFunction();
        void meshGeneration();
};


#endif /* MESH_H_ */
