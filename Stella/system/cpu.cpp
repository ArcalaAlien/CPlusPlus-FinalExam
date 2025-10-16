#include "memory.h"
#include "cpu.h"

namespace Stella
{
    std::list<std::unique_ptr<StellarBase>> CPU::registers;
    std::list<std::unique_ptr<StellarBase>>::iterator CPU::cpuIt = registers.end();

    CPUError CPU::getObjectFromAddress(int address, StellarBase* &obj)
    {
        StellarBase* tempObj = nullptr;
        for (cpuIt = registers.begin(); cpuIt != registers.end(); cpuIt++)
        {
            if ((tempObj = cpuIt->get()) == nullptr)
            {
                std::cerr<<"\nERROR! ATTEMPTED TO GET INVALID ADDRESS FROM CPU REGISTERS!";
                return CPUError_InvalidAddress;
            }

            if (tempObj->getAddress() == address)
            {
                obj = tempObj;
                return CPUError_None;
            }
        }

        obj = nullptr;
        return CPUError_NullPointer;
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
            (baseObjPtr = std::move(Memory::getFromMemory(address))) == nullptr)
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
        StellarBase* baseObj = nullptr;

        for (cpuIt = registers.begin(); cpuIt != registers.end(); cpuIt++)
        {
            if ((baseObj = cpuIt->get()) == nullptr)
            {
                std::cerr<<"\nERROR: UNABLE TO STORE, REGISTER HAS INVALID POINTER OBJECT!";
                cpuIt = registers.end();
                return CPUError_NullPointer;
            }

            baseAddress = baseObj->getAddress();
            if (baseAddress == address && baseAddress >= AllocatorError_None)
            {
                Memory::addToMemory(baseObj);
                cpuIt = removeFromRegister(baseObj);
                break;
            }
        }

        cpuIt = registers.end();
        return CPUError_None;
    }

    CPUError CPU::change(int address, int value)
    {
        StellarBase* baseObj = nullptr;
        getObjectFromAddress(address, baseObj);

        if (baseObj == nullptr)
        {
            std::cerr<<"\nERROR: UNABLE TO CHANGE VALUE OF OBJECT FROM ADDRESS "<<address<<" IN CPU!";
            return CPUError_InvalidAddress;
        }

        std::unique_ptr<StellarBase> newPointer = nullptr;
        Asteroid* tempA;
        switch (baseObj->getType())
        {
            case DataType_Int:
                tempA = dynamic_cast<Asteroid*>(baseObj);
                tempA->viewAs()->setValue(value);
                newPointer.reset(new Asteroid(*tempA));
                break;
            default:
                std::cerr<<"\nERROR: OBJECT HAS AN UNSUPPORTED DATATYPE "<<baseObj->getType();
                return CPUError_InvalidDataType;
        }

        removeFromRegister(baseObj);
        registers.push_back(std::move(newPointer));
        return CPUError_None;
    }

    void CPU::dump()
    {
        std::cout<<"\nThere are "<<registers.size()<<" items in the CPU";
        StellarBase* baseObj;

        int value=0;
        int address=-1;
        DataType dt = DataType_Invalid;

        for (cpuIt = registers.begin(); cpuIt != registers.end(); cpuIt++)
        {
            if (cpuIt->get() != nullptr)
            {
                baseObj=cpuIt->get()->viewAs();
                baseObj->getValue(value);
                address = baseObj->getAddress();
                dt = baseObj->getType();

                std::cout<<"\nAddress: "<<address
                        <<"\nValue: "<<value
                        <<"\nDataType: "<<dt;
            }
        }

        cpuIt = registers.end();
    }

    std::list<std::unique_ptr<StellarBase>>::iterator CPU::removeFromRegister(StellarBase* objPtr)
    {
        for (cpuIt = registers.begin(); cpuIt != registers.end(); cpuIt++)
            if (objPtr->getAddress() == cpuIt->get()->getAddress())
                return registers.erase(cpuIt);

        return cpuIt;
    }
}
