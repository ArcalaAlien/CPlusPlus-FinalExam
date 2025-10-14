// We only want this header to be used once.
#pragma once

#include <iostream>
#include "datatypes.h"

namespace Stella
{
    class MissionControl
    {
        void operator<<(StellarBase*);
    };
}
