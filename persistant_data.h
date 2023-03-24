#pragma once
#include "assert.h"
struct MainState {
    uint32_t state;
    uint32_t systick_counter;
};

struct PersistantDataSingleton {
    uint32_t magic;
    uint32_t rcc_reset_reason;
    uint32_t reset_counter;
    uint32_t reset_magic_before_sw_reset; // Set before reset, cleared on reset
    uint32_t reset_magic_after_sw_reset;  // reset reason is copied here on reset, so check this

    // Store main state here, so we can check it after reset.
    struct MainState main_state;
    struct MainState main_state_before_last_reset; // Copy last main state here at startup.
};

extern struct PersistantDataSingleton persistantData;
static_assert((sizeof(persistantData) & ~3) == sizeof(persistantData), "Persistant data must be word aligned.");