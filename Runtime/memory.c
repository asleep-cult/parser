#include "memory.h"

RuntimeHeap RuntimeHeap_New()
{
        RuntimeHeap heap = {
                .segment_size = 0,
                .segments = NULL
        };
        return heap;
}

MemorySegment *RuntimeHeap_AllocateSegment(RuntimeHeap *heap, size_t size)
{
        heap->segment_size++;
        size_t new_size = sizeof(MemorySegment) * heap->segment_size;
        MemorySegment *segments = realloc(heap->segments, new_size);
        if (segments == NULL) {
                return NULL;
        }
        heap->segments = segments;
        void *data = malloc(sizeof(size));
        if (data == NULL) {
                return NULL;
        }
        heap->segments[heap->segment_size - 1] = (MemorySegment){
                .used = 1,
                .data = data
        }
        MemorySegment *segment = &heap->segments[heap->segment_size - 1];
        return segment;
}

void *RuntimeHeap_Malloc(RuntimeHeap *heap, size_t size)
{
        return RuntimeHeap_AllocateSegment(heap, size)->data;
}

void RuntimeHeap_FreeSegment(RuntimeHeap *heap, int segment_idx)
{
        memmove(
                heap->segments + segment_idx,
                heap->segments + segment_idx + 1,
                sizeof(segment) * (heap->segment_size - segment_idx)
        );
        heap->segment_size--;
}

void RuntimeHeap_FreeUnused(RuntimeHeap *heap)
{
        for (int i = 0; i < heap->segment_size; i++) {
                MemorySegment *segment = &heap->segments[i];
                if (!segment->used) {
                        RuntimeHeap_FreeSegment(heap, i);
                }
        }
}
