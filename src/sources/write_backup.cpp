// #include <vtkActor.h>
// #include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkCellIterator.h>
// #include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkLookupTable.h>
// #include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
// #include <vtkRenderWindow.h>
// #include <vtkRenderWindowInteractor.h>
// #include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>

#include <iterator>
#include <map>
#include <set>

#define USE_POINT_DATA
// Uncomment the next line if you want to use cell data instead
// #undef USE_POINT_DATA

int main(int, char*[])
{
  // vtkNew<vtkNamedColors> colors;

  size_t nx = 2, ny = 3, nz = 2;
  auto dataSize = nx * ny * nz;

  vtkNew<vtkDoubleArray> pointValues;
  pointValues->SetNumberOfComponents(1);
  pointValues->SetNumberOfTuples(dataSize);
  for (size_t i = 0; i < dataSize; ++i)
  {
    pointValues->SetValue(i, i);
  }

  auto numberOfCells = (nx - 1) * (ny - 1) * (nz - 1);
  vtkNew<vtkDoubleArray> cellValues;
  cellValues->SetNumberOfTuples(numberOfCells);
  for (size_t i = 0; i < numberOfCells; ++i)
  {
    cellValues->SetValue(i, i);
  }

  vtkNew<vtkPoints> points;
  auto x = 0.0;
  auto y = 0.0;
  auto z = 0.0;
  for (unsigned int k = 0; k < nz; k++)
  {
    z += 2.0;
    for (unsigned int j = 0; j < ny; j++)
    {
      y += 1.0;
      for (unsigned int i = 0; i < nx; i++)
      {
        x += .5;
        points->InsertNextPoint(x, y, z);
      }
    }
  }

  // Create a grid
  vtkNew<vtkStructuredGrid> structuredGrid;
  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(static_cast<int>(nx), static_cast<int>(ny),
                                static_cast<int>(nz));
  structuredGrid->SetPoints(points);
  structuredGrid->GetCellData()->SetScalars(cellValues);
  structuredGrid->GetPointData()->SetScalars(pointValues);

  // The key is the cell Id and the value is a set of corresponding point Ids.
  std::map<vtkIdType, std::set<vtkIdType>> cellPointIds;
  vtkCellIterator* it = structuredGrid->NewCellIterator();
  for (it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextCell())
  {
    vtkIdList* pointIds = it->GetPointIds();
    std::set<vtkIdType> ptIds;
    for (vtkIdType* id = pointIds->begin(); id != pointIds->end(); ++id)
    {
      ptIds.insert(*id);
    }
    cellPointIds[it->GetCellId()] = ptIds;
  }
  it->Delete();

  // Write file
  vtkNew<vtkXMLStructuredGridWriter> writer;
  writer->SetFileName("output.vts");
  writer->SetInputData(structuredGrid);
  writer->Write();

  return EXIT_SUCCESS;
}
