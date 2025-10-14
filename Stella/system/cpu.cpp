#include <any>

#include "memory.h"
#include "cpu.h"

namespace Stella
{
    std::list<std::unique_ptr<StellarBase>> CPU::registers;

    CPUError CPU::load(int address)
    {
        if (registers.size() >= MAX_REGISTERS)
        {
            std::cerr<<"\nERROR: CPU REGISTERS ARE CURRENTLY FULL!";
            return CPUError_RegistersFull;
        }

        std::unique_ptr<StellarBase> baseObjPointer = nullptr;
        if (!Memory::isAddressAllocated(address) ||
            (baseObjPointer = Memory::getFromMemory(address)) == nullptr)
        {
            std::cerr<<"\nERROR: ATTEMPTED TO GET INVALID ADDRESS "<<address<<" FROM MEMORY!";
            return CPUError_InvalidAddress;
        }

        registers.push_back(std::move(baseObjPointer));
        return CPUError_None;
    }

    CPUError CPU::store(int address)
    {
        if (registers.size() <= 0)
        {
            std::cerr<<"\nERROR: CPU REGISTERS ARE CURRENTLY EMPTY";
            return CPUError_RegistersEmpty;
        }

        if (Memory::isAddressAllocated(address) ||
            Memory::getFromMemory(address) != nullptr)
        {
            std::cerr<<"\nERROR: ATTEMPTED TO OVERWRITE ALLOCATED ADDRESS!";
            return CPUError_InvalidAddress;
        }

        StellarBase *baseObj = nullptr;
        DataType dt = DataType::DataType_Invalid;
        for (std::unique_ptr<StellarBase> &ptrObj: registers)
        {
            baseObj = ptrObj.get();
            

            if (baseObj && (baseObj->getAddress() == address)
            {
                std::cout<<"\nAddress "<<baseObj->getAddress()<<" is equal to "<<address;
                /*
                registers.remove(ptrObj);

                std::unique_ptr<StellarBase> newPtrObj = nullptr;
                switch (dt)
                {
                    case DataType_Int:
                        newPtrObj.reset(baseObj->clone());
                        break;
                    default:
                        return CPUError_InvalidDataType;
                }

                int newAddress = Memory::allocateAddress();
                if (newAddress < AddressAllocatorError::AllocatorError_None)
                    return CPUError_InvalidAddress;

                newPtrObj.get()->setAddress(newAddress);

                registers.push_back(std::move(newPtrObj));
                */
            }
        }

        return CPUError_None;
    }
}
