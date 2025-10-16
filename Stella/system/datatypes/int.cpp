#include <iostream>

#include "int.h"
#include "../cpu.h"

namespace Stella
{
    void Asteroid::testCPU()
    {
        CPUError err;
        if ((err=CPU::load(this->getAddress())) < CPUError::CPUError_None)
        {
            std::cout<<"\nWhoops! CPU was not able to load this address "<<this->getAddress()<<"from memory!";
            return;
        }

        if ((err=CPU::store(this->address)) < CPUError::CPUError_None)
        {
            std::cout<<"\nWhoops! CPU was not able to load this address to memory!";
            return;
        }

        std::cout<<"\nCPU Test Successful!";
    }

    const int Asteroid::getAddress()            { return this->address; }
    void      Asteroid::setAddress(int address) { this->address = address; }

    void Asteroid::getValue(int& value) { value = this->value; }
    void Asteroid::setValue(int value)  { this->value = value; }

    void Asteroid::operator=(int value)
    {
        CPU::load(this->address);
        CPU::dump();
        CPU::change(this->address, value);
        CPU::dump();
        CPU::store(this->address);
        CPU::dump();
    }

    std::ostream& operator<<(std::ostream& output, Asteroid obj)
    {
        int value=0;
        obj.getValue(value);
        output<<value;
        return output;
    }

    std::istream& operator>>(std::istream& input, Asteroid obj)
    {
        int value;
        input>>value;
        obj.setValue(value);
        return input;
    }
}

