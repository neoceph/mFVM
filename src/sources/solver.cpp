#include <Mesh.h>
#include <Solver.h>


Solver::Solver(ControlVolumeMesh *meshObject):mesh(meshObject)
                               
{
}


void Solver::updateResults()
{
    // int a;
    // a = mesh->totalNodes;

    for (size_t i = 0; i < mesh->totalNodes; ++i)
    {
        mesh->nodeScalars->SetValue(i, i);
        mesh->nodeVectors->SetTuple3(i, i, 2*i, 3*i);
        mesh->nodeTensors->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
    }

    for (size_t i = 0; i < mesh->totalCells; ++i)
    {
        mesh->cellScalars->SetValue(i, i);
        mesh->cellVectors->SetTuple3(i, i, 2*i, 3*i);
        mesh->cellTensors->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
    }
}