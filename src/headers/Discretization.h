#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_

// Standard headers

// Third party headers
#include <Eigen/Sparse>

// User defined headers
#include <InputProcessor.h>
#include <Properties.h>


class FiniteVolumeMethod
{
    public:
        // Constructor
        FiniteVolumeMethod(InputProcessor *inputProcessorObject, Properties *propertiesObject);
        // Destructor
        ~FiniteVolumeMethod();

        // Input
        InputProcessor *inputs;
        Properties *properties;

        // Variables
        typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
        std::vector<Eigen::Triplet<double>> triplets;
        typedef Eigen::Triplet<double> T;
        SpMat A;

        // Methods
        void assembleMatrix();
        
};

#endif /* DISCRETIZATION_H_ */
