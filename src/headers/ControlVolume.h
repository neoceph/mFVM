#ifndef ControlVolume_H_
#define ControlVolume_H_

// standard headers
#include <iterator>
#include <map>
#include <set>

// third party headers
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>


class ControlVolume: public vtkDataArray 
{
    public:
        // Constructor
        ControlVolume();
         
        // Destructor
        virtual ~ControlVolume();
    
        // Local functions/subroutines
        void getDomainInfo();

  
};

#endif /* ControlVolume_H_ */
