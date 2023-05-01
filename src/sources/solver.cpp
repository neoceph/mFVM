// Standard headers
#include <math.h>
#include <string>

// Third party headers
#include <Eigen/Sparse>

// User defined headers
#include <Mesh.h>
#include <Solver.h>
#include <Discretization.h>

Solver::Solver
    (
        FiniteVolumeMethod *FVMObject
    ):
    FVM(FVMObject)
                               
{
    // initializing the scalars, vectors, and tensors
    for (auto& stateVariable : FVM->mesh->stateVariables) {

            int numberOfTensorElements = pow(3, stateVariable.second);
            
            // initializing the nodal variables and cell variables by the name of the state variable, the number of components, and the number of tuples
            
            this->nodalVariables[stateVariable.first]->SetName(stateVariable.first.c_str());
            this->nodalVariables[stateVariable.first]->SetNumberOfComponents(numberOfTensorElements);
            this->nodalVariables[stateVariable.first]->SetNumberOfTuples(FVM->mesh->totalNodes);  

            this->cellVariables[stateVariable.first]->SetName(stateVariable.first.c_str());
            this->cellVariables[stateVariable.first]->SetNumberOfComponents(numberOfTensorElements);
            this->cellVariables[stateVariable.first]->SetNumberOfTuples(FVM->mesh->totalCells);  
    }

}

Solver::~Solver()
{
    // TODO Auto-generated destructor stub
}

void Solver::updateResults()
{
    // int a;
    // a = mesh->totalNodes;

    for (size_t i = 0; i < FVM->mesh->totalNodes; ++i)
    {

        for (auto& stateVariable : FVM->mesh->stateVariables) 
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

    for (size_t i = 0; i < FVM->mesh->totalCells; ++i)
    {
        for (auto& stateVariable : FVM->mesh->stateVariables) 
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

void Solver::updateResults(char* stateVariableName, std::vector<double> nodalScalarVariable, std::vector<double> cellScalarVariable)
{
    std::cout<<"State Variable Name :" << stateVariableName << std::endl;
    for (int i=0; i < nodalScalarVariable.size(); i++)
    {
        // std::cout<<"Nodal Scalar Variable Name :" << nodalScalarVariable[i] << std::endl;
        this->nodalVariables[stateVariableName]->SetValue(i, nodalScalarVariable[i]);
    }

    for (int i=0; i < cellScalarVariable.size(); i++)
    {
        // std::cout<<"Nodal Scalar Variable Name :" << nodalScalarVariable[i] << std::endl;
        this->cellVariables[stateVariableName]->SetValue(i, cellScalarVariable[i]);
    }
}

void Solver::updateResults(char* stateVariableName, std::vector<double> nodalScalarVariable)
{
    std::cout<<"State Variable Name :" << stateVariableName << std::endl;
    for (int i=0; i < nodalScalarVariable.size(); i++)
    {
        // std::cout<<"Nodal Scalar Variable Name :" << nodalScalarVariable[i] << std::endl;
        this->nodalVariables[stateVariableName]->SetValue(i, nodalScalarVariable[i]);
    }
}

void Solver::writeData(char* fileName)
{
    vtkNew<vtkXMLStructuredGridWriter> writer;

    for (auto& stateVariable : FVM->mesh->stateVariables) 
    {
        FVM->mesh->controlVolumes->GetPointData()->AddArray(this->nodalVariables[stateVariable.first]);
        FVM->mesh->controlVolumes->GetCellData()->AddArray(this->cellVariables[stateVariable.first]);
    }

    writer->SetFileName(fileName);
    writer->SetInputData(FVM->mesh->controlVolumes);
    writer->Write();
}

void Solver::solve()
{
    // TODO Auto-generated method stub
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.analyzePattern(FVM->A);
    solver.factorize(FVM->A);

    if (solver.info() != Eigen::Success) 
    {
        std::cout << "Factorization failed" << std::endl;
        return;
    }
    Eigen::VectorXd x = solver.solve(FVM->b);
    if (solver.info() != Eigen::Success) 
    {
        std::cout << "Solving failed" << std::endl;
        return;
    }
    // std::cout << "Solution Successful!" << x.transpose() << std::endl;
    std::cout << "Solution Successful!" << std::endl;

}

void Solver::buildPart()
{
    // TODO Auto-generated method stub
    double test;
    test = FVM->mesh->cells[0].faces["East"].coordinate[0];

}