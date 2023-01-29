#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <typeinfo>

// external library headers
#include <Eigen/Dense>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkNew.h>

// self developed library headers
// #include "version.h"
#include "version.h"
#include "Mesh.h"

int main (int arg, char *argv[])
{
    std::cout << "Multiphase solver for Additive Manufacturing Problems!\n";

    VersionInfo version;


    if (arg != 2)
    {
        
        std::cout << "Missing parameter: input file name" << std::endl;
        std::cout << "Printing a test matrix" << std::endl;
        exit(1);
      return 0;
    }

    else
    {
        version.getVersionInfo(argv[1]);
    }


    int array[3] = {0, 1, 2};
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);

    std::cout << m << std::endl;

    std::string s {"Test String"};
    std::vector<double> v (3, 3.14);
    std::list<int> l;

    l.push_back(3);
    l.push_back(1);
    l.push_back(3);


    std::map<int, int> testMap;
    testMap[7] = 2;
    testMap[2] = -987;

    vtkNew<vtkDoubleArray> scalarValue;

    size_t nx = 2, ny = 3, nz = 2;
    auto dataSize = nx * ny * nz;
    auto numberOfCells = (nx - 1) * (ny - 1) * (nz - 1);


    scalarValue->SetName("Mass");
  
    scalarValue->SetNumberOfComponents(1);
    scalarValue->SetNumberOfTuples(dataSize);
    for (size_t i = 0; i < dataSize; ++i)
    {
        scalarValue->SetValue(i, i);
    }



    vtkNew<vtkPoints> points;
    auto x = 0.0;
    auto y = 0.0;
    auto z = 0.0;
    for (unsigned int k = 0; k < nz; k++)
    {
        y = 0.0;
        for (unsigned int j = 0; j < ny; j++)
        {
            x = 0.0;
            for (unsigned int i = 0; i < nx; i++)
            {
                points->InsertNextPoint(x, y, z);
                x += 1.0;
            }
            y += 1.0;
        }
        z += 1.0;
    }

    // vtkNew<ControlVolumeMesh> controlVolumes(size_t nx, size_t ny, size_t nz);
    // vtkNew<ControlVolumeMesh> controlVolumes;
    // vtkNew<vtkStructuredGrid> controlVolumes;
    // ControlVolumeMesh controlVolumes;

    unsigned int dimension = 3;
    std::vector<unsigned int> stepSizes;
    ControlVolumeMesh controlVolumes(nx, ny, nz);

    controlVolumes->SetDimensions(static_cast<int>(nx), static_cast<int>(ny), static_cast<int>(nz));

    controlVolumes->SetPoints(points);
    controlVolumes->GetPointData()->AddArray(scalarValue);

    // cout << controlVolumes.eastFaceArea << endl;



    // Write file
    vtkNew<vtkXMLStructuredGridWriter> writer;
    writer->SetFileName("output.vts");
    writer->SetInputData(controlVolumes);
    writer->Write();

}
