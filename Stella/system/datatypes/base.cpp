#include "base.h"

namespace Stella
{
    const int StellarBase::getAddress()         { return this->address; }
    void StellarBase::setAddress(int address)   { this->address = address; }

    const DataType StellarBase::getType()       { return this->type; }
    void StellarBase::setType(DataType type)    { this->type = type; }

    void StellarBase::getValue(int& value)   { value = this->value; }
    void StellarBase::getValue(float& value) { value = static_cast<float>(this->value); }

    void StellarBase::setValue(int value)   { this->value = value; }
    void StellarBase::setValue(float value) { this->value = value; }

    std::istream& operator>>(std::istream& input, StellarBase& obj)
    {
        int value;
        input>>value;
        obj.setValue(value);
        return input;
    }

    std::ostream& operator<<(std::ostream& output, StellarBase& obj)
    {
        int value;
        obj.getValue(value);
        output<<value;
        return output;
    }
}
