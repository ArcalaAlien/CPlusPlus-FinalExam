#ifndef STL_MEMORYH
#define STL_MEMORYH

#include <memory>
#include <iostream>
#include <map>

#include <utility>

#define MAX_ADDRESSES 64

namespace Stella
{
    // Forward declaration of the base object datatype
    // so we can use it in the memory class.
    class StellarBase;

    enum AddressAllocatorError
    {
        AllocatorError_AddressExists = -2,
        AllocatorError_MemoryOverflow,
        AllocatorError_None
    };

    enum DataType
    {
        DataType_Invalid,
        DataType_Int=0
    };

    class Memory
    {
        private:
            static std::map<int, std::unique_ptr<StellarBase>> memoryMap;

        public:
            static const int                    allocateAddress();
            static bool                         isAddressAllocated(int);
            static const int                    addToMemory(StellarBase*);
            static void                         addToMemory(int&, std::unique_ptr<StellarBase>);
            static std::unique_ptr<StellarBase> getFromMemory(int);
            static void                         printMemory();
    };
}

#endif
