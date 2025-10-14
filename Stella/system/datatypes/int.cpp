#include <iostream>

#include "int.h"
#include "../cpu.h"

namespace Stella
{
    void Asteroid::testCPU()
    {
        CPUError e;
        if ((e=CPU::load(this->getAddress())) > CPUError::CPUError_None)
        {
            std::cout<<"\nWhoops! CPU was not able to load this address "<<this->getAddress()<<"from memory!";
            return;
        }
        std::cout<<"\nSucessfully loaded address "<<this->address<<" from memory into the CPU!";


        if ((e=CPU::store(this->address)) > CPUError::CPUError_None)
        {
            std::cout<<"\nWhoops! CPU was not able to load this address to memory!";
            return;
        }
        std::cout<<"\nSucessfully loaded address "<<this->address<<" from CPU into memory!";
    }

    const int Asteroid::getAddress()            { return this->address; }
    void      Asteroid::setAddress(int address) { this->address = address; }

    const int Asteroid::getValue()              { return this->value; }
    void      Asteroid::setValue(int value)     { this->value = value; }
}

