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
    VersionInfo version;
    vtkNew<vtkXMLStructuredGridWriter> writer;

    std::cout << "Multiphase solver for Additive Manufacturing Problems!\n";


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

    vtkNew<vtkDoubleArray> scalarValue, vectorValue, tensorValue, cellScalars, cellVectors, cellTensors;

    size_t nx = 2, ny = 3, nz = 2;
    auto dataSize = nx * ny * nz;
    auto numberOfCells = (nx - 1) * (ny - 1) * (nz - 1);


    scalarValue->SetName("Mass");
    scalarValue->SetNumberOfComponents(1);
    scalarValue->SetNumberOfTuples(dataSize);

    vectorValue->SetName("Velocity");
    vectorValue->SetNumberOfComponents(3);
    vectorValue->SetNumberOfTuples(dataSize);
    
    tensorValue->SetName("stress");
    tensorValue->SetNumberOfComponents(9);
    tensorValue->SetNumberOfTuples(dataSize);
    
    
    for (size_t i = 0; i < dataSize; ++i)
    {
        scalarValue->SetValue(i, i);
        vectorValue->SetTuple3(i, i, 2*i, 3*i);
        tensorValue->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
    }

    // Cell values
    cellScalars->SetName("Density");
    cellScalars->SetNumberOfTuples(numberOfCells);
    
    cellVectors->SetNumberOfComponents(3);
    cellVectors->SetName("Acceleration");
    cellVectors->SetNumberOfTuples(numberOfCells);

    cellTensors->SetNumberOfComponents(9);
    cellTensors->SetName("Stress");
    cellTensors->SetNumberOfTuples(numberOfCells);


    for (size_t i = 0; i < numberOfCells; ++i)
    {
        cellScalars->SetValue(i, i);
        cellVectors->SetTuple3(i, i, 2*i, 3*i);
        cellTensors->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
    }



    vtkNew<vtkPoints> points;
    auto x = 0.0;
    auto y = 0.0;
    auto z = 0.0;
    double coordinate[3];
    int pointID=0;
    for (unsigned int k = 0; k < nz; k++)
    {
        y = 0.0;
        for (unsigned int j = 0; j < ny; j++)
        {
            x = 0.0;
            for (unsigned int i = 0; i < nx; i++)
            {
                points->InsertNextPoint(x, y, z);
                points->GetPoint(pointID, coordinate);
                // cout<<coordinate<<endl;
                x += 1.0;
                pointID +=1;
            }
            y += 1.0;
        }
        z += 1.0;
    }


    // unsigned int dimension = 3;
    std::vector<unsigned int> stepNumbers{static_cast<uint>(nx), static_cast<uint>(ny), static_cast<uint>(nz)};
    std::vector<double> domainSize{2.0, 3.0, 2.0}; // defining the length of the entire domain


    ControlVolumeMesh mesh(stepNumbers, domainSize);

    mesh.controlVolumes->GetPointData()->AddArray(scalarValue);
    mesh.controlVolumes->GetPointData()->AddArray(vectorValue);
    mesh.controlVolumes->GetPointData()->AddArray(tensorValue);
    
    mesh.controlVolumes->GetCellData()->AddArray(cellScalars);
    mesh.controlVolumes->GetCellData()->AddArray(cellVectors);
    mesh.controlVolumes->GetCellData()->AddArray(cellTensors);

    // cout << controlVolumes.eastFaceArea << endl;

    char fileName[] = "output.vts";

    mesh.writeData(fileName);

}
