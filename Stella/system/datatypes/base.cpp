#include "base.h"

namespace Stella
{
    const int StellarBase::getAddress()         { return this->address; }
    void StellarBase::setAddress(int address)   { this->address = address; }

    const DataType StellarBase::getType()       { return this->type; }
    void StellarBase::setType(DataType type)    { this->type = type; }

    const std::any StellarBase::getValue() { return this->value; }
    void StellarBase::setValue(std::any value) { this->value = std::any_cast<int>(value); }

}
