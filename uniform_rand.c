#include <stdlib.h>

#include "utils.h"


double uniform_rand(double low, double high)
{   
    /* Scale rand() from [0, RAND_MAX] into the target interval [low, high]. */
    return low + (high - low) * ((double)rand() / RAND_MAX);
}
