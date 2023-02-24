#ifndef TESTPROPERTIES_H_
#define TESTPROPERTIES_H_

// Standard headers

// Third party headers


// User defined headers
#include <InputProcessor.h>


class TestProperties
{
    public:
        // Constructor
        TestProperties(InputProcessor *inputProcessorObject);
        // Destructor
        ~TestProperties();

        // Input
        InputProcessor *inputs;
        
        // Variables
        double thermalConductivity = 1000.0; // W/mK
        // typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
        // std::vector<Eigen::Triplet<double>> triplets;
        // typedef Eigen::Triplet<double> T;
        // SpMat A;

        // Methods
        // void assembleMatrix();
        
};

#endif /* TESTPROPERTIES_H_ */
