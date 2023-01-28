// #include <vtkActor.h>
// #include <vtkCamera.h>
// #include <vtkDataSetMapper.h>
// #include <vtkNamedColors.h>
// #include <vtkRenderWindow.h>
// #include <vtkRenderWindowInteractor.h>
// #include <vtkRenderer.h>
// #include <vtkLookupTable.h>
// #include <vtkCellIterator.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>

#include <iterator>
#include <map>
#include <set>

int main(int, char*[])
{

  size_t nx = 2, ny = 3, nz = 2;
  auto dataSize = nx * ny * nz;


  vtkNew<vtkDoubleArray> scalarValue;
  scalarValue->SetName("Mass");
  
  scalarValue->SetNumberOfComponents(1);
  scalarValue->SetNumberOfTuples(dataSize);
  for (size_t i = 0; i < dataSize; ++i)
  {
    scalarValue->SetValue(i, i);
  }

  vtkNew<vtkDoubleArray> vectorValue;
  vectorValue->SetName("Velocity");
  vectorValue->SetNumberOfComponents(3);
  vectorValue->SetNumberOfTuples(dataSize);
  
  vtkNew<vtkDoubleArray> nodeTensorValues;
  nodeTensorValues->SetName("stress");
  nodeTensorValues->SetNumberOfComponents(9);
  nodeTensorValues->SetNumberOfTuples(dataSize);
  
  for (size_t i = 0; i < dataSize; ++i)
  {
    // vectorValue->SetValue(i, i);
    vectorValue->SetTuple3(i, i, 2*i, 3*i);
    nodeTensorValues->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
  }

  auto numberOfCells = (nx - 1) * (ny - 1) * (nz - 1);
  vtkNew<vtkDoubleArray> cellScalars;
  cellScalars->SetName("Density");
  cellScalars->SetNumberOfTuples(numberOfCells);
  
  vtkNew<vtkDoubleArray> cellVectors;
  cellVectors->SetNumberOfComponents(3);
  cellVectors->SetName("Acceleration");
  cellVectors->SetNumberOfTuples(numberOfCells);

  vtkNew<vtkDoubleArray> cellTensorValues;
  cellTensorValues->SetNumberOfComponents(9);
  cellTensorValues->SetName("Stress");
  cellTensorValues->SetNumberOfTuples(numberOfCells);

  for (size_t i = 0; i < numberOfCells; ++i)
  {
    cellScalars->SetValue(i, i);
    cellVectors->SetTuple3(i, i, 2*i, 3*i);
    cellTensorValues->SetTuple9(i, i, 2*i, 3*i, i, 2*i, 3*i, i, 2*i, 3*i);
  }

//creating coordinates for the points to be written in structured grid
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
        points->InsertNextPoint(x, y, z); // point values are ascending x-first, y-second, and z-last
      }
    }
  }

  // Create a grid
  vtkNew<vtkStructuredGrid> structuredGrid;
  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(static_cast<int>(nx), static_cast<int>(ny),
                                static_cast<int>(nz));
  structuredGrid->SetPoints(points);
  structuredGrid->GetCellData()->AddArray(cellScalars);  //setting scalar values to cell centers
  structuredGrid->GetCellData()->AddArray(cellVectors);  //setting vector values to cell centers
  structuredGrid->GetCellData()->AddArray(cellTensorValues);  //setting tensor values to cell centers
  structuredGrid->GetPointData()->AddArray(scalarValue); //setting scalar values to the cell corners/points
  structuredGrid->GetPointData()->AddArray(vectorValue); //setting vector values to the cell corners/points
  structuredGrid->GetPointData()->AddArray(nodeTensorValues); //setting tensor values to the cell corners/points


  // Write file
  vtkNew<vtkXMLStructuredGridWriter> writer;
  writer->SetFileName("output.vts");
  writer->SetInputData(structuredGrid);
  writer->Write();

  return EXIT_SUCCESS;
}
