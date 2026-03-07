#include <stdlib.h>

#include "utils.h"


double uniform_rand(double low, double high)
{   
    return low + (high - low) * ((double)rand() / RAND_MAX);
}
