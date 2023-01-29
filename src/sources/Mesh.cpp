#include <Mesh.h>

ControlVolumeMesh::ControlVolumeMesh(size_t nx, size_t ny, size_t nz)
{
    // constructor definition
    // vtkStructuredGrid::SetDimensions(static_cast<int>(nx), static_cast<int>(ny), static_cast<int>(nz));
}

ControlVolumeMesh::~ControlVolumeMesh()
{
    // destructor definition
}

void ControlVolumeMesh::testFunction()
{
    cout<<"Initializing Meshing..."<<endl;
}


void ControlVolumeMesh::meshGeneration()

{
    int nx, ny, nz;
    ControlVolumeMesh controlVolumes(nx, ny, nz);

}