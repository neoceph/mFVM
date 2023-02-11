#include <Mesh.h>
#include <vtkXMLStructuredGridWriter.h>

ControlVolumeMesh::ControlVolumeMesh(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize)
{
    int totalNodes = stepNumbers[0] * stepNumbers[1] * stepNumbers[2];
    int totalCells = (stepNumbers[0] - 1) * (stepNumbers[1] - 1) * (stepNumbers[2] - 1);
    
    this->controlVolumes->SetDimensions(stepNumbers[0], stepNumbers[1], stepNumbers[2]);
    this->generatePoints(stepNumbers, domainSize);
    this->controlVolumes->SetPoints(this->points);

    // initializing the scalars, vectors, and tensors

    this->nodeScalars->SetName("Mass");
    this->nodeScalars->SetNumberOfComponents(1);
    this->nodeScalars->SetNumberOfTuples(totalNodes);

    this->nodeVectors->SetName("Velocity");
    this->nodeScalars->SetNumberOfComponents(3);
    this->nodeScalars->SetNumberOfTuples(totalNodes);

    this->nodeTensors->SetName("Stress");
    this->nodeScalars->SetNumberOfComponents(9);
    this->nodeScalars->SetNumberOfTuples(totalNodes);

    this->cellScalars->SetName("Mass");
    this->cellScalars->SetNumberOfComponents(1);
    this->cellScalars->SetNumberOfTuples(totalCells);

    this->cellVectors->SetName("Velocity");
    this->cellScalars->SetNumberOfComponents(3);
    this->cellScalars->SetNumberOfTuples(totalCells);

    this->cellTensors->SetName("Stress");
    this->cellScalars->SetNumberOfComponents(9);
    this->cellScalars->SetNumberOfTuples(totalCells);
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

void ControlVolumeMesh::generatePoints(std::vector<unsigned int> stepNumbers, std::vector<double> domainSize)
{
    double xStep, yStep, zStep;

    xStep = domainSize[0] / stepNumbers[0];
    yStep = domainSize[1] / stepNumbers[1];
    zStep = domainSize[2] / stepNumbers[2];


    auto x = 0.0;
    auto y = 0.0;
    auto z = 0.0;
    double coordinate[3];
    int pointID=0;
    for (unsigned int k = 0; k < stepNumbers[2]; k++)
    {
        y = 0.0;
        for (unsigned int j = 0; j < stepNumbers[1]; j++)
        {
            x = 0.0;
            for (unsigned int i = 0; i < stepNumbers[0]; i++)
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
        
    writer->SetFileName(fileName);
    writer->SetInputData(controlVolumes);
    writer->Write();
}