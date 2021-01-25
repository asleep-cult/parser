#include "state.h"
#include "memory.h"

RuntimeState runtime_state = {
        .heap = RuntimeHeap_New()
};
