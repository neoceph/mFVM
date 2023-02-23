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
            size_t nx = 4, ny = 4, nz = 4;
            // size_t nx = 500, ny = 500, nz = 40;
            // size_t nx = 450, ny = 250, nz = 200;

            char fileName[fileNameLength] = "output.vts";
            std::vector<unsigned int> nodeNumbers{static_cast<uint>(nx), static_cast<uint>(ny), static_cast<uint>(nz)};
            std::vector<double> domainDimensions{3.0, 3.0, 3.0}; // defining the length of the entire domain
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
