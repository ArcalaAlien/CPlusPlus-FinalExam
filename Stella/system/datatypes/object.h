#ifndef STL_OBJ
#define STL_OBJ

#include "base.h"

namespace Stella
{
    // This is a base data object so we can make data types
    // using inheritance.
    //
    // Unless you're making a datatype you don't need to call this
    // in your program.
    template <typename T>
    class StellarObject: public StellarBase
    {
        protected:
            T value;

        public:
            // Setting value equal to T() calls the contructor
            // of whatever datatype T might happen
            // to be, and allows us to set value to T's
            // default constructor.
            StellarObject(T value = T()):
                value(value) {}

            virtual ~StellarObject() {}
            // Getter and setter
            virtual const int   getAddress() = 0;
            virtual void        setAddress(int) = 0;

            virtual const T getValue()  = 0;
            virtual void    setValue(T) = 0;

            // This will allow us to return the
            // address of this templated StellarObject child, allowing us to access StellarObject
            // functions no matter the type.
            virtual StellarObject<T>* viewAs() = 0;

            virtual StellarObject<T>* clone() = 0;
    };
}

#endif
