#include "stio.h"
using namespace Stella;

MissionControl& MissionControl::operator|(Asteroid obj)
{
    std::cout<<obj;
    return *this;
}

MissionControl& MissionControl::operator/(StellarBase* obj)
{
    std::cin>>*obj;
    return *this;
}
