#ifndef INPUTPROCESSOR_H_
#define INPUTPROCESSOR_H_

// Standard headers
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <typeinfo>
#include <chrono>

// Third party headers


// User defined headers



class InputProcessor
{
    struct KeyValuePair 
    {
        std::string key;
        int value;
    };
    public:
        // Constructor
        InputProcessor();
        // Destructor
        ~InputProcessor();

        //Input


        //variables
            static const int fileNameLength = 20;
            std::set<std::pair<std::string, int>> stateVariables;
    
            // unsigned int dimension = 3;
            // size_t nx = 2, ny = 4, nz = 4;
            size_t nx = 6, ny = 2, nz = 2;
            // size_t nx = 500, ny = 500, nz = 40;
            // size_t nx = 450, ny = 250, nz = 200;

            // boundary conditions
            double westBoundaryTemperature = 100, eastBoundaryTemperature = 200;

            // heat flux
            double heatFlux = 1000e3; // W/m^2

            char fileName[fileNameLength] = "output.vts";
            std::vector<unsigned int> nodeNumbers{static_cast<uint>(nx), static_cast<uint>(ny), static_cast<uint>(nz)};
            std::vector<double> domainDimensions{2e-2, 1.0, 1.0}; // defining the length of the entire domain
            std::list<KeyValuePair> myList = {
                {"Temp", 0},
                {"Vel", 1},
                {"Stress", 2}
            };

        // methods
            void printFileName();
    private:
        // private variables and methods

};

#endif /* INPUTPROCESSOR_H_ */
