#include "memory.h"
#include "datatypes.h"

namespace Stella
{
    std::map<int, std::unique_ptr<StellarBase>> Memory::memoryMap;

    const int Memory::allocateAddress()
    {
        if (memoryMap.size() >= MAX_ADDRESSES)
            return AllocatorError_MemoryOverflow;

        for (int i=0; i < MAX_ADDRESSES; i++)
        {
            if (memoryMap.find(i) == memoryMap.end())
                return i;
        }

        return AllocatorError_AddressExists;
    }

    bool Memory::isAddressAllocated(int address) { return (memoryMap.find(address) != memoryMap.end()); }

    const int Memory::addToMemory(StellarBase* baseObject)
    {
        // First we'll attempt to set the address for
        // our new object. If allocateAddress() returns
        // less than AllocatorError_None AKA 0
        // we know we've run into an error;

        int newAddress = allocateAddress();
        if (newAddress < AllocatorError_None)
        {
            switch (newAddress)
            {
                case AllocatorError_MemoryOverflow:
                    std::cerr<<"\nERROR: NO ADDRESSES LEFT IN MEMORY!";
                    return newAddress;
                case AllocatorError_AddressExists:
                    std::cerr<<"\nERROR: ADDRESS ALREADY EXISTS IN MEMORY!";
                    return newAddress;
            }
        }

        baseObject->viewAs()->setAddress(newAddress);

        // Now that we've got the address of our object
        // Let's make a unique pointer to it for safe
        // memory manipulation.

        std::unique_ptr<StellarBase> baseObjPtr = nullptr;
        switch (baseObject->getType())
        {
            case DataType_Int:
                baseObjPtr.reset(new Asteroid(*dynamic_cast<Asteroid*>(baseObject)));
                break;
            default:
                std::cerr<<"\nERROR: OBJECT HAS AN UNSUPPORTED DATATYPE "<<baseObject->getType();
                return AllocatorError_InvalidDataType;
        }

        // We've finally got both our pointer, and
        // our new address. We can go ahead and put our
        // object in our memory map.
        //
        // unique_ptrs are non-copyable so we must use std::move()
        // to give the new pair we just made ownership of this pointer.
        memoryMap.insert(std::pair<int, std::unique_ptr<StellarBase>>(newAddress, std::move(baseObjPtr)));
        return newAddress;
    }

    void Memory::addToMemory(int& address, std::unique_ptr<StellarBase> objPtr)
    {
        if (Memory::isAddressAllocated(address))
            address = allocateAddress();

        if (address < AllocatorError_None)
        {
            std::cerr<<"\nERROR! UNABLE TO ADD NEW OBJECT TO MEMORY!";
            return;
        }

        if (!objPtr)
        {
            std::cerr<<"ERROR! UNIQUE_PTR DOESN'T HAVE A VALUE!";
            return;
        }

        memoryMap.insert(std::pair<int, std::unique_ptr<StellarBase>>(address, std::move(objPtr)));
    }

    std::unique_ptr<StellarBase> Memory::getFromMemory(int address)
    {
        if (!isAddressAllocated(address))
            return nullptr;

        std::map<int, std::unique_ptr<StellarBase>>::iterator it = memoryMap.find(address);
        std::unique_ptr<StellarBase> baseObjectPtr = std::move(it->second);
        memoryMap.erase(it);

        return baseObjectPtr;
    }

    void Memory::printMemory()
    {
        std::map<int, std::unique_ptr<StellarBase>>::iterator it;
        std::unique_ptr<StellarBase> basePtr;
        StellarBase* baseObj;

        std::cout<<"\nThere are "<<memoryMap.size()<<" objects in memory.";

        for (int i=0; i < MAX_ADDRESSES; i++)
        {
            if ((it = memoryMap.find(i)) != memoryMap.end())
            {
                basePtr = std::move(it->second);
                baseObj = basePtr.get();
                {
                    Asteroid* tempA = dynamic_cast<Asteroid*>(baseObj);
                    switch (baseObj->getType())
                    {
                        case DataType_Int:
                            if (tempA == nullptr)
                            {
                                std::cout<<"\nFound invalid Asteroid at address: "<<i;
                                break;
                            }

                            std::cout<<"\nFound Asteroid at address: "<<i<<" with value: "<<std::any_cast<int>(tempA->getValue());
                            break;
                        default:
                            break;
                    }
                } // end of code block
            }
        }
    }
}
