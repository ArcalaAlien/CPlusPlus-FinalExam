// We only want this header to be used once.
#pragma once

#include <iostream>
#include "datatypes.h"

namespace Stella
{
    class MissionControl
    {
        public:
            MissionControl() {}

        MissionControl& operator|(Asteroid obj);

        MissionControl& operator/(StellarBase* obj);
    };
}
