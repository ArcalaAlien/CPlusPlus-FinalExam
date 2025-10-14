#ifndef STL_INTH
#define STL_INTH

#include "object.h"

namespace Stella
{
// int
    class Asteroid: public StellarObject<int>
    {
        public:
            Asteroid(int value=0):
                StellarObject()
            {
                this->value     = value;
                this->address   = Memory::addToMemory(this);
                this->type      = DataType::DataType_Int;
            }

            void testCPU();

            const int getAddress();
            void      setAddress(int);

            const std::any getValue();
            void           setValue(int);

            Asteroid* viewAs()  { return dynamic_cast<Asteroid*>(this); }
            Asteroid* clone()   { return new Asteroid(*this); };

            void operator=(int);
    };
}

#endif
