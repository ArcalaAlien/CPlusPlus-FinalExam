#ifndef STL_BASEH
#define STL_BASEH

#include "../memory.h"

namespace Stella
{
    // I had an in depth explanation for why I'm doing this wrote out
    // then it accidentally got overwritten in my clipboard.
    //
    // Essentially, I can't use a template class as a datatype in a container
    // so I have to make this Parent class, then have the template class
    // inherit from this parent class, and use this class in whatever
    // container I need to use it in.
    //
    // Additionally I should use std::unique_ptr when using this as a
    // datatype in a template, as it dynamically creates
    // a pointer to an object, can only point to that one object, and will
    // automatically deallocate it when it gets out of scope.
    class StellarBase
    {
        protected:
            DataType type = DataType::DataType_Invalid;
            int address;
            int value=0;

        public:
            StellarBase(int address=0, int value=0):
                address(address), value(value) {}

            // In order for our std::unique_ptr to be able to
            // deallocate the object we feed it, the object needs
            // a virtual destructor so the unique_ptr can substitute
            // it for its deleter.
            virtual ~StellarBase() {}

            const DataType       getType();
            void                 setType(DataType);
            virtual const int    getAddress();
            virtual void         setAddress(int);

            virtual StellarBase* clone() { return new StellarBase(*this); };
    };
}

#endif
