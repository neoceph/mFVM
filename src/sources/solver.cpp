// Standard headers
#include <math.h>

#include <Mesh.h>
#include <Solver.h>


Solver::Solver(ControlVolumeMesh *meshObject):mesh(meshObject)
                               
{
    // initializing the scalars, vectors, and tensors
    for (auto& stateVariable : mesh->stateVariables) {
        // std::cout << stateVariable.first << " : " << stateVariable.second << std::endl;

            int numberOfTensorElements = pow(3, stateVariable.second);

            this->nodalVariables[stateVariable.first]->SetName(stateVariable.first.c_str());
            this->nodalVariables[stateVariable.first]->SetNumberOfComponents(numberOfTensorElements);
            this->nodalVariables[stateVariable.first]->SetNumberOfTuples(mesh->totalNodes);  

            this->cellVariables[stateVariable.first]->SetName(stateVariable.first.c_str());
            this->cellVariables[stateVariable.first]->SetNumberOfComponents(numberOfTensorElements);
            this->cellVariables[stateVariable.first]->SetNumberOfTuples(mesh->totalCells);  
    }



    // this->nodeScalars->SetName("Temperature");
    // this->nodeScalars->SetNumberOfComponents(1);
    // this->nodeScalars->SetNumberOfTuples(mesh->totalNodes);

    // this->nodeVectors->SetName("Velocity");
    // this->nodeVectors->SetNumberOfComponents(3);
    // this->nodeVectors->SetNumberOfTuples(mesh->totalNodes);

    // this->nodeTensors->SetName("Stress");
    // this->nodeTensors->SetNumberOfComponents(9);
    // this->nodeTensors->SetNumberOfTuples(mesh->totalNodes);

    // this->cellScalars->SetName("Temperature");
    // this->cellScalars->SetNumberOfComponents(1);
    // this->cellScalars->SetNumberOfTuples(mesh->totalCells);

    // this->cellVectors->SetName("Velocity");
    // this->cellVectors->SetNumberOfComponents(3);
    // this->cellVectors->SetNumberOfTuples(mesh->totalCells);

    // this->cellTensors->SetName("Stress");
    // this->cellTensors->SetNumberOfComponents(9);
    // this->cellTensors->SetNumberOfTuples(mesh->totalCells);
}


void Solver::updateResults()
{
    // int a;
    // a = mesh->totalNodes;

    for (size_t i = 0; i < mesh->totalNodes; ++i)
    {
        // this->nodeScalars->SetValue(i, i);
        // this->nodeVectors->SetTuple3(i, i, 2*i, 3*i);
        // this->nodeTensors->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);

        for (auto& stateVariable : mesh->stateVariables) 
        {
            switch(stateVariable.second)
            {
                case 0:
                    this->nodalVariables[stateVariable.first]->SetValue(i, i);
                    break;
                case 1:
                    this->nodalVariables[stateVariable.first]->SetTuple3(i, i, 2*i, 3*i);
                    break;
                case 2:
                    this->nodalVariables[stateVariable.first]->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
                    break;
                default:
                    std::cout<<"State variable not propperly defined"<< std::endl;
                    break;

            }            
        }


    }

    for (size_t i = 0; i < mesh->totalCells; ++i)
    {
        // this->cellScalars->SetValue(i, i);
        // this->cellVectors->SetTuple3(i, i, 2*i, 3*i);
        // this->cellTensors->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);

        for (auto& stateVariable : mesh->stateVariables) 
        {
            switch(stateVariable.second)
            {
                case 0:
                    this->cellVariables[stateVariable.first]->SetValue(i, i);
                    break;
                case 1:
                    this->cellVariables[stateVariable.first]->SetTuple3(i, i, 2*i, 3*i);
                    break;
                case 2:
                    this->cellVariables[stateVariable.first]->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
                    break;
                default:
                    std::cout<<"State variable not propperly defined"<< std::endl;
                    break;

            }            
        }
    }
}

void Solver::writeData(char* fileName)
{
    vtkNew<vtkXMLStructuredGridWriter> writer;

    for (auto& stateVariable : mesh->stateVariables) 
    {
        mesh->controlVolumes->GetPointData()->AddArray(this->nodalVariables[stateVariable.first]);
        mesh->controlVolumes->GetCellData()->AddArray(this->cellVariables[stateVariable.first]);
    }

    // mesh->controlVolumes->GetPointData()->AddArray(this->nodeScalars);
    // mesh->controlVolumes->GetPointData()->AddArray(this->nodeVectors);
    // mesh->controlVolumes->GetPointData()->AddArray(this->nodeTensors);
        
    // mesh->controlVolumes->GetCellData()->AddArray(this->cellScalars);
    // mesh->controlVolumes->GetCellData()->AddArray(this->cellVectors);
    // mesh->controlVolumes->GetCellData()->AddArray(this->cellTensors);

    writer->SetFileName(fileName);
    writer->SetInputData(mesh->controlVolumes);
    writer->Write();
}