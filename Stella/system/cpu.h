#ifndef STL_CPUH
#define STL_CPUH

#include <any>
#include <exception>
#include <list>

#include "datatypes.h"
#include "memory.h"

#define MAX_REGISTERS 32

namespace Stella
{
    enum CPUError
    {
        CPUError_RegistersEmpty,
        CPUError_RegistersFull,
        CPUError_InvalidAddress,
        CPUError_InvalidDataType,
        CPUError_NullPointer,
        CPUError_None = 0
    };

    class CPU
    {
        private:
            static std::list<std::unique_ptr<StellarBase>> registers;

            static const std::unique_ptr<StellarBase> getObjectFromAddress(int);
            static const int getAddressFromObject(std::unique_ptr<StellarBase>);

        public:
            // Load from memory into CPU Register from an address
            static CPUError load(int);

            // Load from CPU Register to Memory
            static CPUError store(int);

            // Change the value of an object in the register.
            static CPUError change(int, std::any);

            // // Add two values
            // StellarBase add(StellarBase, StellarBase);

            // // Subtract two values
            // StellarBase subtract(StellarBase, StellarBase);

            // // Multiply two values
            // StellarBase multiply(StellarBase, StellarBase);

            // // divide two values
            // StellarBase divide(StellarBase, StellarBase);

            // // Compare two values
            // StellarBase compare(StellarBase, StellarBase);

            static void printInRegisters();
    };
}

#endif
