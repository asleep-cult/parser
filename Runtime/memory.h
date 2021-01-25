#include <stdlib.h>

typedef struct MemorySegment {
        int used;
        void *data;
} MemorySegment;

typedef struct RuntimeHeap {
        int segment_size;
        MemorySegment *segments;
} RuntimeHeap;

RuntimeHeap RuntimeHeap_New();
MemorySegment *RuntimeHeap_AllocateSegment(RuntimeHeap *heap, size_t size);
MemorySegment *RuntimeHeap_GetSegment(RuntimeHeap *heap);
void RuntimeHeap_FreeSegment(RuntimeHeap *heap, int segment_idx);
void RuntimeHeap_FreeUnused(RuntimeHeap *heap);
