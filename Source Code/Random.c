// Included Header Files
// ----------------------
#include <stdlib.h>
#include <stdint.h>
#include "Random.h"


// This function initializes the random number generator with the given seed
void Random_Init(uint32_t seed) {
    srand(seed);
}

// This function returns a random uint32_t 
uint32_t Random(void) {
    return rand();
}
