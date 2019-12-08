#include "bsp.h"

/* Function Prototypes */
void assert_failed(const char *file, uint32_t line) {
    /* TODO: Damage Control */

    /* Reset System */
    NVIC_SystemReset();
}

