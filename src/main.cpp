#include<iostream>

#include "version.h"
#include "Eigen/Dense"

int main (int arg, char *argv[])
{
    int array[3] = {0, 1, 2};
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    
    std::cout << "Multiphase solver for Additive Manufacturing Problems!\n";

    if (arg != 2)
    {
        std::cout << "Missing parameter: input file name" << std::endl;
        std::cout << "Printing a test matrix" << std::endl;
        std::cout << m << std::endl;
        exit(1);
      return 0;
    }

    if (strcmp(argv[1], "--version") == 0)
    {
        std::cout << gGIT_VERSION << std::endl;
    }

    else if (strcmp(argv[1], "-v") == 0)
    {
        std::cout << gGIT_VERSION_SHORT << std::endl;
    }    
    // std::cout << gGIT_VERSION << std::endl << gGIT_VERSION_SHORT << std::endl;

    
}