// Standard headers
#include <math.h>
#include <string>

// Third party headers

// User defined headers
#include <Mesh.h>
#include <Solver.h>


Solver::Solver(ControlVolumeMesh *meshObject):mesh(meshObject)
                               
{
    // initializing the scalars, vectors, and tensors
    for (auto& stateVariable : mesh->stateVariables) {

            int numberOfTensorElements = pow(3, stateVariable.second);
            
            // initializing the nodal variables and cell variables by the name of the state variable, the number of components, and the number of tuples
            
            this->nodalVariables[stateVariable.first]->SetName(stateVariable.first.c_str());
            this->nodalVariables[stateVariable.first]->SetNumberOfComponents(numberOfTensorElements);
            this->nodalVariables[stateVariable.first]->SetNumberOfTuples(mesh->totalNodes);  

            this->cellVariables[stateVariable.first]->SetName(stateVariable.first.c_str());
            this->cellVariables[stateVariable.first]->SetNumberOfComponents(numberOfTensorElements);
            this->cellVariables[stateVariable.first]->SetNumberOfTuples(mesh->totalCells);  
    }

}


void Solver::updateResults()
{
    // int a;
    // a = mesh->totalNodes;

    for (size_t i = 0; i < mesh->totalNodes; ++i)
    {

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

    writer->SetFileName(fileName);
    writer->SetInputData(mesh->controlVolumes);
    writer->Write();
}