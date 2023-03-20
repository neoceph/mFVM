#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_

// Standard headers

// Third party headers
#include <Eigen/Sparse>

// User defined headers
#include <InputProcessor.h>
#include <Properties.h>
#include <Mesh.h>


class FiniteVolumeMethod
{
    public:
        // Constructor
        FiniteVolumeMethod(InputProcessor *inputProcessorObject, Properties *propertiesObject, ControlVolumeMesh *meshObject);
        // Destructor
        ~FiniteVolumeMethod();

        // Input
        InputProcessor *inputs;
        Properties *properties;
        ControlVolumeMesh *mesh;

        // Variables
        // typedef Eigen::SparseMatrix<double> SparseMat; // declares a column-major sparse matrix type of double
        // std::vector<Eigen::Triplet<double>> triplets;
        // typedef Eigen::Triplet<double> T;
        // SparseMat A;
        // const Eigen::VectorXd b;

        double  coefficient, westFlux, eastFlux, northFlux, southFlux, topFlux, bottomFlux, pointFlux, 
                dx, dy, dz, pointSource;
        Eigen::SparseMatrix<double> A;
        Eigen::VectorXd b, initialTemperatures;

        // Methods
        void assembleMatrix();
        
};

#endif /* DISCRETIZATION_H_ */
