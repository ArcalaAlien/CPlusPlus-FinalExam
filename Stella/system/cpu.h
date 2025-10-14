#ifndef STL_CPUH
#define STL_CPUH

#include <list>
#include "datatypes.h"
#include "memory.h"

#define MAX_REGISTERS 32

namespace Stella
{
    enum CPUError
    {
        CPUError_None,
        CPUError_RegistersEmpty,
        CPUError_RegistersFull,
        CPUError_InvalidAddress,
        CPUError_InvalidDataType
    };

    class CPU
    {
        private:
            static std::list<std::unique_ptr<StellarBase>> registers;

        public:
            // Load from memory into CPU Register from an address
            static CPUError load(int);

            // Load from CPU Register to Memory
            static CPUError store(int);

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
    };
}

#endif
