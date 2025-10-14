#include "base.h"

namespace Stella
{
    const int StellarBase::getAddress()         { return this->address; }
    void StellarBase::setAddress(int address)   { this->address = address; }

    const DataType StellarBase::getType()       { return this->type; }
    void StellarBase::setType(DataType type)    { this->type = type; }
}
