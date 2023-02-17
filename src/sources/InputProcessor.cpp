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
#include <InputProcessor.h>

InputProcessor::InputProcessor()
{
    // TODO Auto-generated constructor stub
    
    // assigning the key value list pairs to the stateVariables set
    for (auto it = myList.begin(); it != myList.end(); ++it)
    {
        this->stateVariables.insert(std::make_pair(it->key, it->value));
    }

}

InputProcessor::~InputProcessor()
{
    // TODO Auto-generated destructor stub
}

void InputProcessor::printFileName()
{
    // std::cout << "The file name is: " << fileName1 << std::endl;
    std::cout << "The file name is: " << fileName << std::endl;
}