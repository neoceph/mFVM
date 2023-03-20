#ifndef TESTPROPERTIES_H_
#define TESTPROPERTIES_H_

// Standard headers

// Third party headers


// User defined headers
#include <InputProcessor.h>


class Properties
{
    public:
        // Constructor
        Properties(InputProcessor *inputProcessorObject);
        // Destructor
        ~Properties();

        // Input
        InputProcessor *inputs;
        
        // Variables
        double thermalConductivity = 0.5; // W/mK


        // Methods

        
};

#endif /* TESTPROPERTIES_H_ */
