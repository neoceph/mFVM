#include <Mesh.h>
#include <vtkXMLStructuredGridWriter.h>

ControlVolumeMesh::ControlVolumeMesh(std::vector<unsigned int> nodeNumbers, std::vector<double> domainDimensions)
{
    totalNodes = nodeNumbers[0] * nodeNumbers[1] * nodeNumbers[2];
    totalCells = (nodeNumbers[0] - 1) * (nodeNumbers[1] - 1) * (nodeNumbers[2] - 1);
    
    this->controlVolumes->SetDimensions(nodeNumbers[0], nodeNumbers[1], nodeNumbers[2]);
    this->generatePoints(nodeNumbers, domainDimensions);
    this->controlVolumes->SetPoints(this->points);

    // initializing the scalars, vectors, and tensors

    this->nodeScalars->SetName("Mass");
    this->nodeScalars->SetNumberOfComponents(1);
    this->nodeScalars->SetNumberOfTuples(totalNodes);

    this->nodeVectors->SetName("Velocity");
    this->nodeVectors->SetNumberOfComponents(3);
    this->nodeVectors->SetNumberOfTuples(totalNodes);

    this->nodeTensors->SetName("Stress");
    this->nodeTensors->SetNumberOfComponents(9);
    this->nodeTensors->SetNumberOfTuples(totalNodes);

    this->cellScalars->SetName("Mass");
    this->cellScalars->SetNumberOfComponents(1);
    this->cellScalars->SetNumberOfTuples(totalCells);

    this->cellVectors->SetName("Velocity");
    this->cellVectors->SetNumberOfComponents(3);
    this->cellVectors->SetNumberOfTuples(totalCells);

    this->cellTensors->SetName("Stress");
    this->cellTensors->SetNumberOfComponents(9);
    this->cellTensors->SetNumberOfTuples(totalCells);
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
                points->GetPoint(pointID, coordinate);
                x += xStep;
                pointID +=1;
                
            }
            y += yStep;
        }
        z += zStep;
    }
}



void ControlVolumeMesh::writeData(char* fileName)
{
    vtkNew<vtkXMLStructuredGridWriter> writer;

    this->controlVolumes->GetPointData()->AddArray(this->nodeScalars);
    this->controlVolumes->GetPointData()->AddArray(this->nodeVectors);
    this->controlVolumes->GetPointData()->AddArray(this->nodeTensors);
        
    this->controlVolumes->GetCellData()->AddArray(this->cellScalars);
    this->controlVolumes->GetCellData()->AddArray(this->cellVectors);
    this->controlVolumes->GetCellData()->AddArray(this->cellTensors);

    writer->SetFileName(fileName);
    writer->SetInputData(controlVolumes);
    writer->Write();
}