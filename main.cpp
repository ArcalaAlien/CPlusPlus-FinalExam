#include "Stella/Stella.h"
using namespace Stella;

int main()
{
    MissionControl houston;
    Asteroid a, b;

    Memory::printMemory();

    a = 5;
    b = 3;

    Memory::printMemory();

    houston | a;

    return 0;
}
