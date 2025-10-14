#include <any>

#include "memory.h"
#include "cpu.h"

namespace Stella
{
    std::list<std::unique_ptr<StellarBase>> CPU::registers;

    const std::unique_ptr<StellarBase> CPU::getObjectFromAddress(int address)
    {
        for (std::unique_ptr<StellarBase> &objPtr: registers)
            if (objPtr->viewAs()->getAddress() == address)
                return std::move(objPtr);

        return nullptr;
    }

    const int CPU::getAddressFromObject(std::unique_ptr<StellarBase> obj)
    {
        for (std::unique_ptr<StellarBase> &objPtr: registers)
            if (objPtr == obj)
                return objPtr->viewAs()->getAddress();

        return CPUError_InvalidAddress;
    }

    CPUError CPU::load(int address)
    {
        if (registers.size() >= MAX_REGISTERS)
        {
            std::cerr<<"\nERROR: CPU REGISTERS ARE CURRENTLY FULL!";
            return CPUError_RegistersFull;
        }

        std::unique_ptr<StellarBase> baseObjPtr = nullptr;
        if (!Memory::isAddressAllocated(address) ||
            (baseObjPtr = Memory::getFromMemory(address)) == nullptr)
        {
            std::cerr<<"\nERROR: ATTEMPTED TO GET INVALID ADDRESS "<<address<<" FROM MEMORY!";
            return CPUError_InvalidAddress;
        }

        if (!baseObjPtr)
        {
            std::cerr<<"\nERROR: NULL POINTER ATTEMPTING TO BE PASSED TO CPU REGISTER!";
            return CPUError_NullPointer;
        }

        std::unique_ptr<StellarBase> newPtr = nullptr;
        switch(baseObjPtr->getType())
        {
            case DataType_Int:
                newPtr.reset(new Asteroid(*dynamic_cast<Asteroid*>(baseObjPtr.get())));
                break;
            default:
                std::cerr<<"\nERROR: OBJECT HAS AN UNSUPPORTED DATATYPE "<<baseObjPtr->getType();
                return CPUError_InvalidDataType;
        }

        registers.push_back(std::move(newPtr));
        return CPUError_None;
    }

    CPUError CPU::store(int address)
    {
        if (registers.size() <= 0)
        {
            std::cerr<<"\nERROR: CPU REGISTERS ARE CURRENTLY EMPTY";
            return CPUError_RegistersEmpty;
        }

        int baseAddress=-1;
        StellarBase* baseObj;

        std::list<std::unique_ptr<StellarBase>>::iterator it;
        while (it != registers.end())
        {
            std::unique_ptr<StellarBase> baseObjPtr = std::move(*it);

            if (baseObjPtr == nullptr)
            {
                std::cerr<<"\nERROR: UNABLE TO STORE, REGISTER HAS INVALID POINTER OBJECT!";
                return CPUError_NullPointer;
            }

            baseAddress = baseObjPtr->getAddress();
            if (baseAddress == address && baseAddress >= AllocatorError_None)
            {
                int newAddress = Memory::allocateAddress();
                if (newAddress < AddressAllocatorError::AllocatorError_None)
                    return CPUError_InvalidAddress;

                std::unique_ptr<StellarBase> newobjPtr;
                switch (baseObjPtr->getType())
                {
                    case DataType_Int:
                        newobjPtr.reset(new Asteroid(*dynamic_cast<Asteroid*>(baseObj)));
                        break;
                    default:
                        return CPUError_InvalidDataType;
                }

                Memory::addToMemory(newAddress, std::move(newobjPtr));
            }

            it++;
        }

        return CPUError_None;
    }

    CPUError CPU::change(int address, std::any value)
    {
        std::unique_ptr<StellarBase> obj = getObjectFromAddress(address);

        if (!obj)
        {
            std::cerr<<"\nERROR: UNABLE TO FIND OBJECT FROM ADDRESS "<<address;
            return CPUError_InvalidAddress;
        }

        StellarBase* baseObj = obj.get();
        {
            Asteroid* tempA;
            switch (obj->getType())
            {
                case DataType_Int:
                    tempA = dynamic_cast<Asteroid*>(baseObj);
                    tempA->setValue(std::any_cast<int>(value));
                    obj.reset(new Asteroid(*tempA));
                    break;
                default:
                    std::cerr<<"\nERROR: OBJECT HAS AN UNSUPPORTED DATATYPE "<<obj->getType();
                    return CPUError_InvalidDataType;
            }
        }

        registers.remove(obj);
        registers.push_back(std::move(obj));
        return CPUError_None;
    }

    void CPU::printInRegisters()
    {
        for (std::unique_ptr<StellarBase> &baseObj: registers)
        {

        }
    }
}
