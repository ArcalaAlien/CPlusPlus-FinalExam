#ifndef STL_INTH
#define STL_INTH

#include "object.h"

namespace Stella
{
// int
    class Asteroid: public StellarObject<int>
    {
        friend std::istream& operator>>(std::istream&, Asteroid);
        friend std::ostream& operator<<(std::ostream&, Asteroid);

        public:
            Asteroid(int value=0):
                StellarObject()
            {
                this->value     = value;
                this->address   = Memory::addToMemory(this);
                this->type      = DataType::DataType_Int;

                std::cout<<"\nAsteroid created with value: "<<this->value<<" at address: "<<this->address;
            }

            void testCPU();

            const int getAddress();
            void      setAddress(int);

            void getValue(int&);
            void setValue(int);

            Asteroid* viewAs()  { return dynamic_cast<Asteroid*>(this); }
            Asteroid* clone()   { return new Asteroid(*this); };

            void operator=(int);
    };
}

#endif
